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
	glPushMatrix(); { //								#Draw robot start
		//master location status
		glTranslated(0, (st->ysize) / 2, 0); // move to the Y-axis center of robot
		glRotated(90.0, 0, 1, 0); // rotate the robot proper way (following mouse mothion command)
		glPushMatrix(); { //							#Draw body start
			glTranslated(0, (st->ysize) / 10, 0); // move to the Y-axis center of body
			glPushMatrix(); { //						#Draw legs start
				glTranslated(0, -(st->ysize) / 10 * 3, 0); //move to the Y-axis center of upper legs
				glColor3f(1.0, 0.0, 0.0); // upper leg color : red
				glPushMatrix(); { //					#Draw upper left leg start
					glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of upper left leg
					glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper left leg
					glutSolidCube((st->ysize) / 5); // draw upper left leg
				} glPopMatrix(); // [upper left leg end]
				glPushMatrix(); { //					#Draw upper right leg start
					glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of upper right leg
					glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
					glutSolidCube((st->ysize) / 5); // draw upper right leg
				} glPopMatrix(); // [upper right leg end]

				glPushMatrix(); { //					#Draw lower leg start
					glColor3f(0.0, 1.0, 0.0); // lower leg color : green
					glTranslated(0, -(st->ysize) / 5, 0); // move to the Y-axis center of lower legs
					glPushMatrix(); { //				#Draw lower left leg start
						glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of lower left leg
						glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower left leg
						glutSolidCube((st->ysize) / 5); // draw lower left leg
					} glPopMatrix(); // [lower left leg end]
					glPushMatrix(); { //				#Draw lower right leg start
						glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of lower right leg
						glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower right leg
						glutSolidCube((st->ysize) / 5); // draw lower right leg
					} glPopMatrix(); // [lower right leg end]
				} glPopMatrix(); // [lower leg end]
			} glPopMatrix(); // [leg end]
			glColor3f(1.0, 1.0, 1.0);// body color : white
			glScaled(0.7,1.0,(st->zsize)/(st->ysize)*5/4); // -- rescale body
			glutSolidCube((st->ysize)/5*2); // draw body
		} glPopMatrix(); // [body end]
		glPushMatrix(); { //							#Draw head start
			glTranslated(0, (st->ysize) / 5 * 2, 0); // move to the Y-axis center of head
			glScaled(1.0, 1.0, (st->zsize) / (st->ysize) * 5 / 3); // -- rescale head
			glColor3f(0.0, 0.0, 1.0); // head color : blue
			glutSolidCube((st->ysize) / 5); // draw head
		} glPopMatrix(); //[head end]
		glPushMatrix(); { //							#Draw arms start
			glTranslated(0, (st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
			glColor3f(1.0, 0.0, 0.0); // upper arms color : red
			glPushMatrix(); { //						#Draw upper left arm start
				glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
				glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
				glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
			} glPopMatrix(); // [upper left arm end]
			glPushMatrix(); { //						#Draw upper right arm start
				glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of right upper arm
				glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // --rescale right upper arm
				glutSolidCube((st->ysize) / 10 * 3); // draw right upper arm
			} glPopMatrix(); // [upper right arm end]

			glPushMatrix(); { //						#Draw lower arm start
				glColor3f(0.0, 1.0, 0.0); // lower arms color : green
				glTranslated(0, -(st->ysize) / 10 * 3, 0);
				glPushMatrix(); { //					#Draw left lower arm start
					glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left lower arm
					glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left lower arm
					glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
				} glPopMatrix(); // [lower left arm end]
				glPushMatrix(); { //					#Draw right lower amr start
					glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of right lower arm
					glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale right lower arm
					glutSolidCube((st->ysize) / 10 * 3); // draw right lower arm
				} glPopMatrix(); // [lower right arm end]
			} glPopMatrix(); // [lower arm end]
		} glPopMatrix(); // [arms end]
	} glPopMatrix(); // [robot end]
}


Zaku_Graphic::Zaku_Graphic(status* in) : Graphic(in) {}
Zaku_Graphic::~Zaku_Graphic() {}
void Zaku_Graphic::draw() {
	glPushMatrix(); { //								#Draw robot start
					  //master location status
		glTranslated(st->x, 0, st->z);
		glTranslated(0, 50.0, 0);
		glRotated(-st->degree, 0, 1, 0);
		glPushMatrix(); { //							#Draw body start
			glTranslated(0, (st->ysize) / 10, 0); // move to the Y-axis center of body
			glPushMatrix(); { //						#Draw legs start
				glTranslated(0, -(st->ysize) / 10 * 3, 0); //move to the Y-axis center of upper legs
				glColor3f(0.5, 0.5, 0.0); // upper leg color : red
				glPushMatrix(); { //					#Draw upper left leg start
					glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of upper left leg
					glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper left leg
					glutSolidCube((st->ysize) / 5); // draw upper left leg
				} glPopMatrix(); // [upper left leg end]
				glPushMatrix(); { //					#Draw upper right leg start
					glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of upper right leg
					glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
					glutSolidCube((st->ysize) / 5); // draw upper right leg
				} glPopMatrix(); // [upper right leg end]

				glPushMatrix(); { //					#Draw lower leg start
					glColor3f(0.0, 0.5, 0.5); // lower leg color : green
					glTranslated(0, -(st->ysize) / 5, 0); // move to the Y-axis center of lower legs
					glPushMatrix(); { //				#Draw lower left leg start
						glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of lower left leg
						glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower left leg
						glutSolidCube((st->ysize) / 5); // draw lower left leg
					} glPopMatrix(); // [lower left leg end]
					glPushMatrix(); { //				#Draw lower right leg start
						glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of lower right leg
						glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower right leg
						glutSolidCube((st->ysize) / 5); // draw lower right leg
					} glPopMatrix(); // [lower right leg end]
				} glPopMatrix(); // [lower leg end]
			} glPopMatrix(); // [leg end]
			glColor3f(0.5, 0.5, 0.0);// body color : white
			glScaled(0.7, 1.0, (st->zsize) / (st->ysize) * 5 / 4); // -- rescale body
			glutSolidCube((st->ysize) / 5 * 2); // draw body
		} glPopMatrix(); // [body end]
		glPushMatrix(); { //							#Draw head start
			glTranslated(0, (st->ysize) / 5 * 2, 0); // move to the Y-axis center of head
			glScaled(1.0, 1.0, (st->zsize) / (st->ysize) * 5 / 3); // -- rescale head
			glColor3f(0.0, 0.5, 0.0); // head color : blue
			glutSolidCube((st->ysize) / 5); // draw head
		} glPopMatrix(); //[head end]
		glPushMatrix(); { //							#Draw arms start
			glTranslated(0, (st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
			glColor3f(0.5, 0.5, 0.0); // upper arms color : red
			glPushMatrix(); { //						#Draw upper left arm start
				glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
				glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
				glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
			} glPopMatrix(); // [upper left arm end]
			glPushMatrix(); { //						#Draw upper right arm start
				glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of right upper arm
				glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // --rescale right upper arm
				glutSolidCube((st->ysize) / 10 * 3); // draw right upper arm
			} glPopMatrix(); // [upper right arm end]

			glPushMatrix(); { //						#Draw lower arm start
				glColor3f(0.0, 0.5, 0.5); // lower arms color : green
				glTranslated(0, -(st->ysize) / 10 * 3, 0);
				glPushMatrix(); { //					#Draw left lower arm start
					glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left lower arm
					glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left lower arm
					glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
				} glPopMatrix(); // [lower left arm end]
				glPushMatrix(); { //					#Draw right lower amr start
					glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of right lower arm
					glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale right lower arm
					glutSolidCube((st->ysize) / 10 * 3); // draw right lower arm
				} glPopMatrix(); // [lower right arm end]
			} glPopMatrix(); // [lower arm end]
		} glPopMatrix(); // [arms end]
	} glPopMatrix(); // [robot end]
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

GUI::GUI() {}
GUI::~GUI() {}
void GUI::draw() {

}