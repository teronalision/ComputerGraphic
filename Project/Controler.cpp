#include "Controler.h"


void ctrinit(Object** t) {
	taget = t;
}
void Keybord(unsigned char key, int x, int y) {

	switch (key)
	{
	case 'w':
		taget[0]->myP->vz = -1;
		break;
	case 'a':
		taget[0]->myP->vx = -1;
		break;
	case 's':
		taget[0]->myP->vz = 1;
		break;
	case 'd':
		taget[0]->myP->vx = 1;
		break;
	case ' ':
		taget[0]->myP->jump_count = 1;
		break;
	default:
		break;
	}
}

void MouseClick(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		for (int i = 1; i < OBJMAX; i++) {
			if (taget[i] == NULL) {
					taget[i] = new Bullet(taget[0]->myS.x, taget[0]->myS.z, taget[0]->myS.degree);
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
	oldx = x;
	oldy = y;
}
