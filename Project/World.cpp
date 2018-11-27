#include "World.h"



World::World()
{
	objects[0] = new Object();
	objects[0]->myG = new Box();
	objects[0]->myS = new status();

}


World::~World()
{
}

void World::worlddraw() {
	

	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, y = feild[i][j], z = j * 100;
			glVertex3i(x, y, z);
			glVertex3i(x+100, y, z);
			glVertex3i(x+100, y, z+100);
			glVertex3i(x, y, z+100);
		}
	}
	glEnd();


	for (int i = 0; i < 100; i++) {
		if (objects[i] != NULL)
			objects[i]->myG->draw(*objects[i]->myS);
	}
}

Object::Object() {
	myG, myP, myS = NULL;
}