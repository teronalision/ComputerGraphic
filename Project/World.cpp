#include "World.h"



World::World()
{
	objects[0].myG = new Gundam(&(objects[0].myS));
	objects[0].myP = new Physic(&(objects[0].myS));
	objects[1].myG = new Field(&(objects[0].myS));
	objects[1].myP = new Physic(&(objects[1].myS));
}


World::~World()
{
}

void World::worlddraw() {
	
	gluLookAt(300*cos((objects[0].myS.degree + 90.0)*R), objects[0].myS.y + 150, 300*sin((objects[0].myS.degree + 90.0)*R), 0, 0, 0, 0, 1, 0);


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
		if (objects[i].myG != NULL)
			objects[i].myG->draw();
	}
}

void World::worldupdate() {
	for (int i = 0; i < 100; i++) {
		if (objects[i].myP != NULL)
			objects[i].myP->PhyUpdate();
	}
}

Object::Object() {
	myG, myP= NULL;
}