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
	
	for (int i = 0; i < RESOLUTION; i++) {
		for (int j = 0; j < RESOLUTION; j++) {
			field[i][j] = map[i*RESOLUTION +j];
		}
	}
	objects[0] = new G();
}


World::~World()
{
}


void World::worlddraw() {
	//ModelInit();
	//gluLookAt(-sin((objects[0]->myS.degree)*R)*5,2,cos((objects[0]->myS.degree)*R)*5, 0, 0, 0, 0, 1, 0);
	glTranslated(0,-2,-5);
	glRotated(10,1,0,0);
	glRotated(Graphic::gety(),1,0,0);
	objects[0]->myG->draw();

	glRotated(objects[0]->myS.degree,0,1,0);
	glTranslated(-objects[0]->myS.x, -objects[0]->myS.y, objects[0]->myS.z);

	glBegin(GL_QUADS);
	glColor3f(0,0,0.3);
	glVertex3f(0,water,0);
	glVertex3f(1000, water, 0);
	glVertex3f(1000, water, -1000);
	glVertex3f(0, water, -1000);
	glEnd();

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < RESOLUTION; i++) {
		for (int j = 0; j < RESOLUTION; j++) {
			int t = 1000 / RESOLUTION;
			int x = j*t, z = -i*t;
			int p[4] = { field[i][j] ,field[i][j+1] ,field[i+1][j] ,field[i+1][j+1] };

			glNormal3f(p[0]-p[1],1,p[2]-p[0]);
			glColor3f(0, p[0]/255.0,0);
			glVertex3i(x, p[0], z);
			glVertex3i(x + t, p[1], z);
			glVertex3i(x + t, p[3], z-t);
			glVertex3i(x, p[2], z - t);
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
	if (objects[0]->myS.hp <= 0)
		state = _gameover;
	objects[0]->update();
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		objects[i]->update();

		if (objects[i]->myS.hp <= 0)
			objects[i]->myS.live = false;

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

	if (worldinfo.state == _play) {
		int hour = 0;
		int minute = 0;
		int second = 0;

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2, WIN_H / 2, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		glClear(GL_DEPTH_BUFFER_BIT);

		//HP_GREEN
		if (hp > 0) {
			glColor3f(0.0, 1.0, 0.0);
			glBegin(GL_QUADS);
			glVertex3d(-230, 180, 1);
			glVertex3d(-230, 170, 1);
			glVertex3d(-230 + hp * 6, 170, 1);
			glVertex3d(-230 + hp * 6, 180, 1);
			glEnd();
		}

		//HP_RED
		glColor3f(1.0, 0.0, 0.0);
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
		glVertex3d(150 + (worldinfo.objects[0]->myS.x) / 1000 * 90, -190 + (worldinfo.objects[0]->myS.z) / 1000 * 90, 1.0);
		glEnd();

		//Timer Information
		hour = (int)(worldinfo.worldtime / 3600);
		minute = (int)(worldinfo.worldtime - hour * 3600) / 60;
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
		glRasterPos2d(-5, 55);
		len = (int)strlen(string);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		glColor3f(0.5, 0.5, 0.5);
		string = "|";
		glRasterPos2d(-0.5003, 55);
		len = (int)strlen(string);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else if (worldinfo.state == _pause) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2, WIN_H / 2, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		glClear(GL_DEPTH_BUFFER_BIT);

		glColor3f(1.0, 1.0, 1.0);
		GLubyte* texbits;
		BITMAPINFO*texture;

		GLuint textures[4];

		glGenTextures(4, textures);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		texbits = Loadbmp("PAUSE.bmp", &texture);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, 450, 150, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texbits);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_DECAL);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2d(-225, 75);
		glTexCoord2f(0.0, 0.0);
		glVertex2d(-225, -75);
		glTexCoord2f(1.0, 0.0);
		glVertex2d(225, -75);
		glTexCoord2f(1.0, 1.0);
		glVertex2d(225, 75);
		glEnd();

		glDisable(GL_TEXTURE_2D);



		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	else if (worldinfo.state == _gameover) {
		int hour = 0;
		int minute = 0;
		int second = 0;

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(-WIN_W / 2, WIN_W / 2, -WIN_H / 2, WIN_H / 2, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_CULL_FACE);
		glDisable(GL_LIGHTING);

		glClear(GL_DEPTH_BUFFER_BIT);

		glColor3f(1.0, 1.0, 1.0);
		GLubyte* texbits;
		BITMAPINFO*texture;

		GLuint textures[4];

		glGenTextures(4, textures);

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		texbits = Loadbmp("Died.bmp", &texture);

		glTexImage2D(GL_TEXTURE_2D, 0, 3, 450, 150, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, texbits);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_DECAL);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2d(-225, 75);
		glTexCoord2f(0.0, 0.0);
		glVertex2d(-225, -75);
		glTexCoord2f(1.0, 0.0);
		glVertex2d(225, -75);
		glTexCoord2f(1.0, 1.0);
		glVertex2d(225, 75);
		glEnd();


		//Timer Information
		hour = (int)(worldinfo.worldtime / 3600);
		minute = (int)(worldinfo.worldtime - hour * 3600) / 60;
		second = (int)(worldinfo.worldtime - hour * 3600) % 60;

		glColor3f(1.0, 0.0, 0.0);
		char string3[23];
		sprintf(string3, "You Lived %02d : %02d : %02d", hour, minute, second);
		glRasterPos2d(-225, -85);
		int len = (int)strlen(string3);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string3[i]);

		glDisable(GL_TEXTURE_2D);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
}

void ModelInit() {
	GLfloat qaBlack[] = { 0.0,0.0,0.0,1.0 };
	GLfloat qaGreen[] = { 1.0,1.0,1.0,1.0 };
	GLfloat qaWhite[] = { 0.5,0.5,0.5,0.5 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, qaBlack);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaBlack);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT, GL_SHININESS, 3.0);
}

void DrawSun(double x, double y, double z) {
	glPushMatrix(); {
		glTranslated(x, y, z);
		glColor3f(1.0, 1.0, 0.9);
		glutSolidSphere(50, 12, 12);
	}glPopMatrix();
}

void SunLight(double x, double y, double z) {

	DrawSun(-200, 1000, 200);

	GLfloat qaAmbientLight[] = { 0.2,0.2,0.2,1.0 };
	GLfloat qaDiffuseLight[] = { 0.7,0.7,0.7,1.0 };
	GLfloat qaSpecularLight[] = { 0.9,0.9,0.9,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	GLfloat qaLightPosition[] = { 0 , 800, 0, 1.0 };
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
	int time = int(worldtime) % 100;
	if (time > 0 && wave == 0) {
		for (int i = 0; i < 5; i++)
			addOBJ(zaku_a, rand() % 100 + 150, 30, rand() % 100 + 310, 90);

		wave++;
	}
	if (time > 40 && wave == 1) {
		for (int i = 0; i < 8; i++)
			addOBJ(zaku_a, rand() % 300 + 550, 30, rand() % 200 + 700, 90);

		wave++;
	}
	
	if (time > 80 && wave == 3) {
		for (int i = 0; i < 12; i++)
			addOBJ(zaku_a, rand() % 200 + 650, 30, rand() % 200 + 400, 90);

		wave = 0;
	}

	if (rand() % 100 == 0) {
		addOBJ(zaku);
	}
}