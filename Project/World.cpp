#define _CRT_SECURE_NO_WARNINGS
#include "World.h"

GLubyte* Loadbmp(const char* filename, BITMAPINFO** info) {
	FILE *f;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((f = fopen(filename, "rb")) == NULL)
		return NULL;
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, f) < 1) {
		fclose(f);
		return NULL;
	}
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(f);
		exit(0);
		return NULL;
	}
	if (fread(*info, 1, infosize, f) < (unsigned int)infosize) {
		free(*info);
		fclose(f);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(f);
		return NULL;
	}
	fread(bits, 1, bitsize, f);
	fclose(f);
	return bits;
}
World::World()
{
	srand(time(NULL));

	GLubyte *map;
	BITMAPINFO *info;
	map = Loadbmp("map.bmp", &info);
	loadmap(map);
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			field[i][j] = map[i*100+j];
		}
	}
	objects[0] = new G();

}


World::~World()
{
}


void World::worlddraw() {
	
	//gluLookAt(-sin((objects[0]->myS.degree)*R)*5,2,cos((objects[0]->myS.degree)*R)*5, 0, 0, 0, 0, 1, 0);
	glTranslated(0,-2,-4);
	objects[0]->myG->draw();

	glRotated(objects[0]->myS.degree,0,1,0);
	glTranslated(-objects[0]->myS.x, -objects[0]->myS.y, objects[0]->myS.z);

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = j * 10, z = i * -10;
			glColor3f(j/100.0,0,i/100.0);
			glVertex3i(x, field[i][j], z);
			glVertex3i(x + 10, field[i][j + 1], z);
			glVertex3i(x+10, field[i+1][j+1], z-10);
			glVertex3i(x, field[i + 1][j], z - 10);
		}
	}
	glEnd();
	glPopMatrix();


	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] != NULL)
			objects[i]->myG->draw();
	}
	SunLight(objects[0]->myS.x, objects[0]->myS.y, objects[0]->myS.z);
}

void World::worldupdate() {
	for (int i = 0; i < OBJMAX; i++) {
		for (int j = 1; j < OBJMAX; j++) {//충돌검사
			if (objects[i] == NULL || objects[j] == NULL)
				continue;

			if (objects[i]->checkName(bullet) && objects[j]->checkName(zaku)
				&& is_crash(objects[i]->myS, objects[j]->myS)) {
				objects[i]->myS.live = false;
				objects[j]->myS.live = false;
				std::cout << "충돌 : " << j << "자쿠와 " << i << "총알" << std::endl;
			}
		}
	}

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		if (objects[i]->checkName(zaku) && is_crash(objects[0]->myS, objects[i]->myS)) {
			objects[i]->myS.live = false;
			std::cout << "충돌 : 건담과 " << i << "자쿠" << std::endl;
		}
	}


	for (int i = 0; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		objects[i]->myP->PhyUpdate();

		if (objects[i]->myS.live == false) {//객체 삭제
			objects[i]->Kill();
			delete objects[i];
			objects[i] = NULL;
		}
	}

	if (rand() % 100 == 0) {
		addOBJ(zaku);
	}

}

void World::addOBJ(_name o, int x, int y, int z, double d) {
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL) {

			switch (o)
			{
			case zaku:
				objects[i] = new Zaku(i);
				break;
			case bullet:
				objects[i] = new Bullet(i, x, 0, z, d);
				break;
			default:
				break;
			}
		}
	}
}

void GUIdraw() {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-WIN_W / 2, WIN_W / 2, -WIN_H / 2, WIN_H / 2);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2d(-100, 100);
	glVertex2d(100, 100);
	glVertex2d(100, -100);
	glVertex2d(-100, -100);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void ModelInit() {
	glNormal3f(0.0, 0.0, 1.0);
	GLfloat qaBlack[] = { 0.0,0.0,0.0,1.0 };
	GLfloat qaGreen[] = { 1.0,1.0,1.0,1.0 };
	GLfloat qaWhite[] = { 0.5,0.5,0.5,0.5 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 60.0);
}

void SunLight(double x, double y, double z) {

	GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	GLfloat qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	GLfloat qaLightPosition[] = { x ,y + 10000, z, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, qaAmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	glEnable(GL_LIGHT0);
}