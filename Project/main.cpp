#include <gl/freeglut.h>
#include "Controler.h"
#include "World.h"

World world;


void Timerf(int value) {
	
	if(world.state == _play)
		world.worldupdate();

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, Timerf, 1);
}
GLvoid DrawScene(GLvoid) {
	glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	
	if (world.state == _play) {
		glutSetCursor(GLUT_CURSOR_NONE);
		glPushMatrix();
		world.worlddraw();
		glPopMatrix();
		GUIdraw(world.objects[0]->myS.hp, world.objects[0]->magazin, world); // temporary function
	}
	else {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		GUIdraw(world.objects[0]->myS.hp, world.objects[0]->magazin, world); // temporary function
	}

	glutSwapBuffers();
}
GLvoid Reshape(int w, int h) {
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, WIN_W/(float)WIN_H, 1.0, 3000.0);
	glTranslated(0.0, 0.0, 0.0);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
}


void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIN_W*2, WIN_H*2);
	glutCreateWindow("Window");


	ctrinit(&world);
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(MouseClick);
	glutPassiveMotionFunc(MouseMove);
	glutTimerFunc(1000 / FPS, Timerf, 1);
	glutMainLoop();
}