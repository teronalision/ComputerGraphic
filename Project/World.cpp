#include "World.h"



World::World()
{
	objects[0] = new Object();
	objects[0]->myG = new Box(&(objects[0]->myS));
	objects[0]->myP = new Physic(&(objects[0]->myS));
}


World::~World()
{
}

void World::worlddraw() {
	
	gluLookAt(objects[0]->myS.x, objects[0]->myS.y + 100, objects[0]->myS.z + 500, objects[0]->myS.x, 0, objects[0]->myS.z, 0, 1, 0);
	glRotated(objects[0]->myS.degree, 0, 1, 0);

	glPushMatrix();
		glColor3f(0.5, 0.5, 0.0);
		glScaled(1.0, 0.001, 1.0);
		glTranslated(500.0, 0.0, -500.0);
		glutSolidCube(1000.0);
	glPopMatrix();


	/*glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, y = feild[i][j], z = j * 100;
			glColor3f(0.5,0.5,i/100.0);
			glVertex3i(x, y, z);
			glVertex3i(x+100, y, z);
			glVertex3i(x+100, y, z+100);
			glVertex3i(x, y, z+100);
		}
	}
	glEnd();*/


	for (int i = 0; i < 100; i++) {
		if (objects[i] != NULL)
			objects[i]->myG->draw();
	}
}

void World::worldupdate() {
	for (int i = 0; i < 100; i++) {
		if (objects[i] != NULL)
			objects[i]->myP->PhyUpdate();
	}
}

Object::Object() {
	myG, myP= NULL;
}