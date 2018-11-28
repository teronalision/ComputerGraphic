#include "Controler.h"


void ctrinit(Object* t) {
	taget = t;
}
void Keybord(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'w':
		taget->myS.speed += 1;
		break;
	case 'a':
		//taget->myS.x -= 1;
		break;
	case 's':
		taget->myS.speed -= 1;
		break;
	case 'd':
		//taget->myS.x += 1;
		break;
	default:
		break;
	}
}

void MouseClick(int button, int state, int x, int y) {}
void MouseMove(int x, int y) {
	if (x < WIN_W - 100)
		taget->myS.degree -= 1;
	else if (x > WIN_W + 100)
		taget->myS.degree += 1;
}
