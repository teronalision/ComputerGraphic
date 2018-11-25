#include "Graphic.h"


Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

Box::Box(){}

Box::~Box(){}

void Box::draw() {
	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(100);
}