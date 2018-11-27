#include "Controler.h"


void ctrinit(Object* t) {
	taget = t;
}
void Keybord(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'w':
		taget->myS->z += 5;
		break;
	case 'a':
		taget->myS->x -= 5;
		break;
	case 's':
		taget->myS->z -= 5;
		break;
	case 'd':
		taget->myS->x += 5;
		break;
	default:
		break;
	}

}
void MouseClick(int button, int state, int x, int y) {}
void MouseMove(int x, int y) {}
