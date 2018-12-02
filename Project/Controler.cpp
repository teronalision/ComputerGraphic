#include "Controler.h"


void ctrinit(Object* t) {
	taget = t;
}
void Keybord(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'w':
		taget->myP->vz = -1;
		break;
	case 'a':
		taget->myP->vx = -1;
		break;
	case 's':
		taget->myP->vz = 1;
		break;
	case 'd':
		taget->myP->vx = 1;
		break;
	case ' ':
		taget->myP->jump_count = 1;
		break;
	default:
		break;
	}
}

void MouseClick(int button, int state, int x, int y) {}
void MouseMove(int x, int y) {
	static int oldx =0, oldy =0;

	if(oldx >x)
		taget->myS.degree -= 1;
	else if (oldx < x)
		taget->myS.degree += 1;
	oldx = x;
	oldy = y;
}
