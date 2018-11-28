#include "Graphic.h"


Graphic::Graphic(status* in)
{
	st = in;
}

Graphic::~Graphic()
{
}

Box::Box(status* in):Graphic(in) {

}

Box::~Box(){}

void Box::draw() {
	glPushMatrix();
	glTranslated(st->x,st->y,st->z);

	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(100);

	glPopMatrix();
}