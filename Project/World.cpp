#include "World.h"



World::World()
{
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			field[i][j] = rand() % 200 -100;
		}
	}
	objects[0] = new G(0,500,500);

}


World::~World()
{
}


void World::worlddraw() {
	
	gluLookAt(300*cos((objects[0]->myS.degree + 90.0)*R), 150, 300*sin((objects[0]->myS.degree + 90.0)*R), 0, 100, 0, 0, 1, 0);

	objects[0]->myG->draw();
	glTranslated(-objects[0]->myS.x, -objects[0]->myS.y, -objects[0]->myS.z);

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, z = -j * 100;
			glColor3f(0.5,0.5,i/100.0);
			glVertex3i(x, field[j+1][i], z);
			glVertex3i(x, field[j][i], z + 100);
			glVertex3i(x+100, field[j][i+1], z+100);
			glVertex3i(x + 100, field[j+1][i+1], z);
		}
	}
	glEnd();
	glPopMatrix();
	/*glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, z = -j * 100;
			glColor3f(0.5, 0.5, i / 100.0);
			glVertex3i(x, field[j + 1][i]+1, z);
			glVertex3i(x, field[j][i]+1, z + 100);
			glVertex3i(x + 100, field[j][i + 1]+1, z + 100);
			glVertex3i(x + 100, field[j + 1][i + 1]+1, z);
		}
	}
	glEnd();
	glPopMatrix();*/

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] != NULL)
			objects[i]->myG->draw();
	}
}

void World::worldupdate() {
	
	for (int i = 0; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		for (int j = 1; j < OBJMAX; j++) {//Ãæµ¹Ã³¸®
			if (objects[j] == NULL)
				continue;

			if (objects[i]->checkName(bullet) && objects[j]->checkName(zaku)
				&& is_crash(objects[i]->myS, objects[j]->myS)) {
				objects[i]->myS.live = false;
				objects[j]->myS.live = false;
				std::cout << "Ãæµ¹ : "<< j << "ÃÑ¾Ë°ú " << j << "ÀÚÄí" << std::endl;
			}
		}

	}

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		if (objects[i]->checkName(zaku) && is_crash(objects[0]->myS, objects[i]->myS)) {
			objects[i]->myS.live = false;
			std::cout << "Ãæµ¹ : °Ç´ã°ú " << i << "ÀÚÄí" << std::endl;
		}
	}


	for (int i = 0; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		objects[i]->myP->PhyUpdate();//°´Ã¼ ¾÷µ¥ÀÌÆ®

		if (objects[i]->myS.live == false) {//Á×ÀÌ±â
			objects[i]->Kill();
			delete objects[i];
			objects[i] = NULL;
		}
	}


	//ÀÚÄí ·£´ý»ý¼º 30%
	if (rand() % 100 == 0) {
		int r = rand() % 360;
		addOBJ(zaku, 450*sin(r*R) +500, 100, 450*cos(r*R) +500, (r*R)+R);
	}

}

void World::addOBJ(_name o,int x, int y, int z,double d) {
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL) {
			switch (o)
			{
			case zaku:
				objects[i] = new Zaku(i, x,y,z,d);
				break;
			case bullet:
				objects[i] = new Bullet(i, x,0,z,d);
				break;
			default:
				break;
			}
			break;
		}
	}

}