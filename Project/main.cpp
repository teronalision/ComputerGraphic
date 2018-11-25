#include <gl/freeglut.h>
#include "Physic.h"
#include "Graphic.h"
#include "World.h"

#define FPS 30
#define WIN_H 400
#define WIN_W 500



void Timerf(int value) {
	


	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timerf, 1);
}
GLvoid DrawScene(GLvoid) {
	/*for (int i = 0; i < World::getObjNum; i++) {
		World::ObjList[i].myG.draw()
	}*/
}
GLvoid Reshape(int w, int h) {}
void Keybord(unsigned char key, int x, int y) {}
void MouseClick(int button, int state, int x, int y){}
void MouseMove(int x, int y) {}


void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIN_W*2, WIN_H*2);
	glutCreateWindow("Window");

	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keybord);
	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutTimerFunc(1000 / FPS, Timerf, 1);
	glutMainLoop();
}