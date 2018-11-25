#include <gl/freeglut.h>
#include "Physic.h"
#include "Graphic.h"
#include "World.h"

#define FPS 30
#define WIN_H 400.0
#define WIN_W 500.0
#define DIS 500


void Timerf(int value) {
	


	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timerf, 1);
}
GLvoid DrawScene(GLvoid) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	/*for (int i = 0; i < World::getObjNum; i++) {
		World::ObjList[i].myG.draw()
	}*/

	//юс╫ц
	glRotated(15,-1,0,0);
	glRotated(15,0,-1,0);
	Box g;
	g.draw();


	glPopMatrix();
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, WIN_W/WIN_H, 1.0, 1000.0);
	glTranslated(0.0, 0.0, -5.0);
	glOrtho(-DIS, DIS, -DIS, DIS, -DIS, DIS);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
}
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