#include "World.h"



World::World()
{
	objects[0] = new G(0,0);

}


World::~World()
{
}


void World::worlddraw() {
	
	gluLookAt(300*cos((objects[0]->myS.degree + 90.0)*R), 150, 300*sin((objects[0]->myS.degree + 90.0)*R), 0, 100, 0, 0, 1, 0);

	objects[0]->myG->draw();
	glTranslated(-objects[0]->myS.x, -objects[0]->myS.y, -objects[0]->myS.z);


	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, y = feild[i][j], z = -j * 100;
			glColor3f(0.5,0.5,i/100.0);
			glVertex3i(x, y, z);
			glVertex3i(x, y, z + 100);
			glVertex3i(x+100, y, z+100);
			glVertex3i(x + 100, y, z);
		}
	}
	glEnd();


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

void World::addOBJ(name o,int x, int z,double d) {
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL) {
			switch (o)
			{
			case gundam:
				objects[i] = new G(x,z);
				break;
			case zaku:
				objects[i] = new Zaku(x, z);
				break;
			case bullet:
				objects[i] = new Bullet(x, z,d);
				break;
			default:
				break;
			}
		}
	}

}