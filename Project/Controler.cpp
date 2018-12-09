#include "Controler.h"


void ctrinit(World* t) {
	ww = t;
	taget = t->objects;
}
void KeyboardDown(unsigned char key, int x, int y) {
	Physic& hero = *(taget[0]->myP);

	switch (key)
	{
	case 'w':
		hero.vz = 1;
		break;
	case 'a':
		hero.vx = -1;
		break;
	case 's':
		hero.vz = -1;
		break;
	case 'd':
		hero.vx = 1;
		break;
	case ' ':
		hero.vy = 10;
		break;
	default:
		break;
	}
}
void KeyboardUp(unsigned char key, int x, int y) {
	Physic& hero = *(taget[0]->myP);
	switch (key)
	{
	case 'w':
		hero.vz -= 1;
		break;
	case 'a':
		hero.vx += 1;
		break;
	case 's':
		hero.vz += 1;
		break;
	case 'd':
		hero.vx -= 1;
		break;
	default:
		break;
	}
}
void MouseClick(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (taget[0]->is_fire() == false)
			return;

		for (int i = 1; i < OBJMAX; i++) {
			if (taget[i] == NULL) {
					taget[i] = new Bullet(i, taget[0]->myS.x, taget[0]->myS.y, taget[0]->myS.z, taget[0]->myS.degree);
					return;
			}
		}
	}

}
void MouseMove(int x, int y) {
	static int oldx =0, oldy =0;

	if(oldx >x)
		taget[0]->myS.degree -= 1;
	else if (oldx < x)
		taget[0]->myS.degree += 1;

	if (oldy >y)
		ww->Yaim -= 0.1;
	else if (oldy < y)
		ww->Yaim += 0.1;
	oldx = x;
	oldy = y;
}
