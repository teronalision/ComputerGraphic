#include "Graphic.h"


Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

Box::Box(){}

Box::~Box(){}

void Box::draw(status s) {
	glPushMatrix();
	glTranslated(s.x,s.y,s.z);

	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(100);

	glPopMatrix();
}