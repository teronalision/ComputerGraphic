#include "World.h"



World::World()
{
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			field[i][j] = rand() % 200;
		}
	}
	objects[0] = new G(0,0);

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
		if (objects[i] != NULL)
			objects[i]->myP->PhyUpdate();
	}
}
