#include "Controler.h"


void ctrinit(World* t) {
	ww = t;
	taget = t->objects;
}
void KeyboardDown(unsigned char key, int x, int y) {
	Physic& hero = *(taget[0]->myP);

	switch (key)
	{
	case 27:
		if (ww->state == _play)
			ww->state = _pause;
		else if (ww->state == _pause)
			ww->state = _play;
		break;
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
		hero.vy = 3;
		que::push_q(jumppaticle,hero.st->x, hero.st->y, hero.st->z);
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
		taget[0]->fire();
	}

}
void MouseMove(int x, int y) {
	int oldx =WIN_W, oldy =WIN_H;

	if(oldx >x)
		taget[0]->myS.degree -= 0.8;
	else if (oldx < x)
		taget[0]->myS.degree += 0.8;

	if (oldy > y)
		Graphic::sety(-0.2);
	else if (oldy < y)
		Graphic::sety(0.2);

	if(ww->state == _play)
		glutWarpPointer(WIN_W,WIN_H);
}
