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
	state = _play;
	worldtime = 0;
	srand(time(NULL));

	GLubyte *map;
	BITMAPINFO *info;
	map = Loadbmp("map1.bmp", &info);
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
	glTranslated(0,-2,-5);
	glRotated(10,1,0,0);
	glRotated(Graphic::gety(),1,0,0);
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
	SunLight(500, 0, -500 );
}

void World::worldupdate() {
	for (int i = 0; i < OBJMAX; i++) {
		for (int j = 1; j < OBJMAX; j++) {//충돌검사
			if (objects[i] == NULL || objects[j] == NULL)
				continue;

			if (objects[i]->checkName(bullet) && objects[j]->checkName(zaku)
				&& is_crash(objects[i]->myS, objects[j]->myS)) {
				objects[j]->myS.hp -= objects[i]->myS.hp;
				objects[i]->myS.live = false;
				que::push_q(d_paticle, objects[j]->myS.x, objects[j]->myS.y, objects[j]->myS.z);
				knockback(objects[j]->myP, *(objects[i]->myP));
				if (objects[j]->myS.hp < 0)
					objects[j]->myS.live = false;
				std::cout << "충돌 : " << j << "자쿠와 " << i << "총알" << std::endl;
			}
		}
	}

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		if (objects[i]->checkName(zaku) && is_crash(objects[0]->myS, objects[i]->myS)) {
			objects[0]->myS.hp -= 1;
			objects[i]->myS.live = false;
			std::cout << "충돌 : 건담과 " << i << "자쿠" << std::endl;
		}

		else if (objects[i]->checkName(bullet_z) && is_crash(objects[0]->myS, objects[i]->myS)) {
			objects[0]->myS.hp -= 1;
			objects[i]->myS.live = false;
			std::cout << "충돌 : 건담 피격! " << std::endl;
		}
	}


	for (int i = 0; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		objects[i]->update();

		if (objects[i]->myS.live == false) {//객체 삭제
			if (objects[i]->Kill()) {
				delete objects[i];
				objects[i] = NULL;
			}
		}
	}
	
	//pop que
	Object* re = que::pop_q();
	while (re != NULL) {
		for (int i = 1; i < OBJMAX; i++) {
			if (objects[i] == NULL) {
				objects[i] = re;
				objects[i]->ID = i;
				break;
			}
		}
		re = que::pop_q();
	}


	if (rand() % 300 == 0) {
		addOBJ(zaku);
	}
	WaveControl();
	worldtime += 1.0/FPS;
}

void World::addOBJ(_name o, int x, int y, int z, double d) {
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL) {

			switch (o)
			{
			case zaku:
				objects[i] = new Zaku(i);
				break;
			case zaku_a:
				objects[i] = new Zaku(i, x, y, z, d);
				break;
			case bullet:
				objects[i] = new Bullet(i, x, 0, z, d);
				break;
			default:
				break;
			}
			break;
		}
	}
}

void GUIdraw(int hp, int bullet, World worldinfo) {

	int hour = 0;
	int minute = 0;
	int second = 0;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2, WIN_H / 2,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);

	glClear(GL_DEPTH_BUFFER_BIT);

	//HP_GREEN
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(-230, 180, 1);
	glVertex3d(-230, 170, 1);
	glVertex3d(-230 + hp*6, 170, 1);
	glVertex3d(-230 + hp*6, 180, 1);
	glEnd();

	//HP_RED
	glColor3f(1.0,0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex3d(-230, 180, 1);
	glVertex3d(-230, 170, 1);
	glVertex3d(-230 + 120, 170, 1);
	glVertex3d(-230 + 120, 180, 1);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	char *string = "HP";
	glRasterPos2d(-230, 180);
	int len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);


	//Bullets
	string = "BULLET";
	glRasterPos2d(-230, -160);
	len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);

	if (bullet == 0) {
		string = "RELOADING...";
		glRasterPos2d(-230, -180);
		len = (int)strlen(string);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
	else {
		char string2[6];
		sprintf(string2, "%2d/20", bullet);
		glRasterPos2d(-230, -180);
		len = (int)strlen(string2);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string2[i]);
	}

	//Maps - Mapsize = 90x90 / Worldsize = 1,000
	glColor4f(0.5, 0.5, 0.5, 0.0);
	glBegin(GL_QUADS);
	glVertex2d(240, -100);
	glVertex2d(240, -190);
	glVertex2d(150, -190);
	glVertex2d(150, -100);
	glEnd();
	//Gundam Location
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex3d(150+(worldinfo.objects[0]->myS.x)/1000*90, -190+(worldinfo.objects[0]->myS.z)/1000*90, 1.0);
	glEnd();

	//Timer Information
	hour = (int)(worldinfo.worldtime/3600);
	minute = (int)(worldinfo.worldtime - hour * 3600)/60;
	second = (int)(worldinfo.worldtime - hour * 3600) % 60;

	glColor3f(1.0, 1.0, 0.0);
	char string3[13];
	sprintf(string3, "%02d : %02d : %02d", hour, minute, second);
	glRasterPos2d(190, 180);
	len = (int)strlen(string3);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string3[i]);

	//Zaku Location
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	for (int i = 1; i < 100; i++)
	{
		if (worldinfo.objects[i] == NULL)
			continue;
		if (worldinfo.objects[i]->checkName(zaku)) {
			glVertex3d(150 + (worldinfo.objects[i]->myS.x) / 1000 * 90, -190 + (worldinfo.objects[i]->myS.z) / 1000 * 90, 1.0);
		}
	}
	glEnd();

	//Aim GUI
	glColor3f(0.5, 0.5, 0.5);
	string = "--";
	glRasterPos2d(-5, 85);
	len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	glColor3f(0.5, 0.5, 0.5);
	string = "|";
	glRasterPos2d(-0.5003, 85);
	len = (int)strlen(string);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
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

void DrawSun(double x, double y, double z) {
	glPushMatrix(); {
		glTranslated(x, y, z);
		glColor3f(1.0, 1.0, 0.0);
		glutSolidSphere(20, 10, 10);
	}glPopMatrix();
}

void SunLight(double x, double y, double z) {

	DrawSun(0, 1000, 0);

	GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };
	GLfloat qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	GLfloat qaLightPosition[] = { 0 , 1000, 0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);


	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	GLfloat qaLightPosition2[] = { 0 ,1, 0, 0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition2);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, qaAmbientLight);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0.0);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
}

void World::WaveControl() {
	static int wave = 0;
	int time = int(worldtime) % 120;
	if (time > 0 && wave == 0) {
		for (int i = 0; i < 5; i++)
			addOBJ(zaku_a, rand() % 100 + 50, 30, rand() % 400 + 300, 90);

		wave++;
	}
	if (time > 40 && wave == 1) {
		for (int i = 0; i < 8; i++)
			addOBJ(zaku_a, rand() % 100 + 850, 30, rand() % 400 + 300, 90);

		wave++;
	}
	
	if (time > 80 && wave == 3) {
		for (int i = 0; i < 10; i++)
			addOBJ(zaku_a, rand() % 400 + 300, 30, rand() % 100 + 850, 90);

		wave = 0;
	}
}