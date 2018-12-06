#include "Graphic.h"


Graphic::Graphic(status* in)
{
	st = in;
}

Graphic::~Graphic()
{
}

Box::Box(status* in):Graphic(in) {}
Box::~Box(){}
void Box::draw() {
	glPushMatrix();
	glTranslated(st->x,st->y,st->z);

	glColor3f(1.0, 0.0, 0.0);
	glutWireCube(100);

	glPopMatrix();
}


Gundam::Gundam(status* in) : Graphic(in) {}
Gundam::~Gundam() {}
void Gundam::draw() {
	glPushMatrix(); {
		glTranslated(0, 50.0, 0);
		glRotated(-st->degree, 0, 1, 0);
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix(); {
			//head
			glTranslated(0, 40.0, 0);
			glutSolidCube(20);
			glPushMatrix(); {
				//chest
				glTranslated(0, -25, 0);
				glPushMatrix(); {
					//BackEngine left
					glTranslated(-10, 0.0, 20.0);
					glScaled(1.0, 1.5, 1.0);
					glColor3f(0.0, 0.0, 1.0);
					glutSolidCube(10);
				}
				glPopMatrix();
				glPushMatrix(); {
					//BackEngine right
					glTranslated(10, 0.0, 20.0);
					glScaled(1.0, 1.5, 1.0);
					glColor3f(0.0, 0.0, 1.0);
					glutSolidCube(10);
				}
				glPopMatrix();
				glPushMatrix(); {
					//left arm up
					glTranslated(-30, 0.0, 0.0);
					glPushMatrix(); {
						//left arm down
						glTranslated(0.0, -20.0, 0.0);
						glScaled(1.0, 2.0, 1.0);
						glColor3f(1.0, 0.0, 0.0);
						glutSolidCube(15);
					}
					glPopMatrix();
					glScaled(1.0, 2.0, 1.0);
					glColor3f(1.0, 1.0, 1.0);
					glutSolidCube(15);
				}
				glPopMatrix();
				glPushMatrix(); {
					//right arm up
					glTranslated(30, 0.0, 0.0);
					glPushMatrix(); {
						//right arm down
						glTranslated(0.0, -20.0, 0.0);
						glScaled(1.0, 2.0, 1.0);
						glColor3f(1.0, 0.0, 0.0);
						glutSolidCube(15);
					}
					glPopMatrix();
					glScaled(1.0, 2.0, 1.0);
					glColor3f(1.0, 1.0, 1.0);
					glutSolidCube(15);
				}
				glPopMatrix();
				glColor3f(1.0, 0.0, 1.0);
				glScaled(0.8, 0.5, 0.5);
				glutSolidCube(60);
			}
			glPopMatrix();
			glPushMatrix(); {
				//stomach
				glColor3f(1.0, 1.0, 0.0);
				glTranslated(0, -40, 0);
				glScaled(0.5, 0.3, 0.3);
				glutSolidCube(70);
			}
			glPopMatrix();
			glPushMatrix(); {
				//left leg up
				glTranslated(-10, -50, 0);
				glScaled(1.0, 2.0, 1.0);
				glColor3f(1.0, 1.0, 1.0);
				glutSolidCube(15);
				glPushMatrix(); {
					//left leg down
					glColor3f(1.0, 0.0, 0.0);
					glTranslated(0, -15, 0);
					glutSolidCube(15);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix(); {
				//right leg up
				glTranslated(10, -50, 0);
				glScaled(1.0, 2.0, 1.0);
				glColor3f(1.0, 1.0, 1.0);
				glutSolidCube(15);
				glPushMatrix(); {
					//right leg down
					glColor3f(1.0, 0.0, 0.0);
					glTranslated(0, -15, 0);
					glutSolidCube(15);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

Zaku_Graphic::Zaku_Graphic(status* in) : Graphic(in) {}
Zaku_Graphic::~Zaku_Graphic() {}
void Zaku_Graphic::draw() {
	glPushMatrix(); {
		glTranslated(rand()%1000, 0, rand()%1000);
		glTranslated(0, 50.0, 0);
		glRotated(-st->degree, 0, 1, 0);
		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix(); {
			//head
			glTranslated(0, 40.0, 0);
			glutSolidCube(20);
			glPushMatrix(); {
				//chest
				glTranslated(0, -25, 0);
				glPushMatrix(); {
					//BackEngine left
					glTranslated(-10, 0.0, 20.0);
					glScaled(1.0, 1.5, 1.0);
					glColor3f(0.0, 0.0, 1.0);
					glutSolidCube(10);
				}
				glPopMatrix();
				glPushMatrix(); {
					//BackEngine right
					glTranslated(10, 0.0, 20.0);
					glScaled(1.0, 1.5, 1.0);
					glColor3f(0.0, 0.0, 1.0);
					glutSolidCube(10);
				}
				glPopMatrix();
				glPushMatrix(); {
					//left arm up
					glTranslated(-30, 0.0, 0.0);
					glPushMatrix(); {
						//left arm down
						glTranslated(0.0, -20.0, 0.0);
						glScaled(1.0, 2.0, 1.0);
						glColor3f(1.0, 0.0, 0.0);
						glutSolidCube(15);
					}
					glPopMatrix();
					glScaled(1.0, 2.0, 1.0);
					glColor3f(1.0, 1.0, 1.0);
					glutSolidCube(15);
				}
				glPopMatrix();
				glPushMatrix(); {
					//right arm up
					glTranslated(30, 0.0, 0.0);
					glPushMatrix(); {
						//right arm down
						glTranslated(0.0, -20.0, 0.0);
						glScaled(1.0, 2.0, 1.0);
						glColor3f(1.0, 0.0, 0.0);
						glutSolidCube(15);
					}
					glPopMatrix();
					glScaled(1.0, 2.0, 1.0);
					glColor3f(1.0, 1.0, 1.0);
					glutSolidCube(15);
				}
				glPopMatrix();
				glColor3f(1.0, 0.0, 1.0);
				glScaled(0.8, 0.5, 0.5);
				glutSolidCube(60);
			}
			glPopMatrix();
			glPushMatrix(); {
				//stomach
				glColor3f(1.0, 1.0, 0.0);
				glTranslated(0, -40, 0);
				glScaled(0.5, 0.3, 0.3);
				glutSolidCube(70);
			}
			glPopMatrix();
			glPushMatrix(); {
				//left leg up
				glTranslated(-10, -50, 0);
				glScaled(1.0, 2.0, 1.0);
				glColor3f(1.0, 1.0, 1.0);
				glutSolidCube(15);
				glPushMatrix(); {
					//left leg down
					glColor3f(1.0, 0.0, 0.0);
					glTranslated(0, -15, 0);
					glutSolidCube(15);
				}
				glPopMatrix();
			}
			glPopMatrix();
			glPushMatrix(); {
				//right leg up
				glTranslated(10, -50, 0);
				glScaled(1.0, 2.0, 1.0);
				glColor3f(1.0, 1.0, 1.0);
				glutSolidCube(15);
				glPushMatrix(); {
					//right leg down
					glColor3f(1.0, 0.0, 0.0);
					glTranslated(0, -15, 0);
					glutSolidCube(15);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}



Field::Field(status*in) :Graphic(in) {};
Field::~Field() {}
void Field::draw() {
	glPushMatrix(); {
		glTranslated(-st->x, -st->y, -st->z);
		glTranslated(500.0, 0.0, -500.0);
		glScaled(1.0, 0.001, 1.0);
		glColor3f(0.5, 0.5, 0.0);
		glutSolidCube(1000.0);
	} glPopMatrix();
}