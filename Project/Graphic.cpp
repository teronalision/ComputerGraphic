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

Bullet_Graphic::Bullet_Graphic(status*in) : Graphic(in) {}
Bullet_Graphic::~Bullet_Graphic() {}
void Bullet_Graphic::draw() {
	glPushMatrix();
	glTranslated(st->x, st->y, -st->z);
	glColor3f(1.0, 1.0, 0.0);
	glRotated(90 -st->degree, 0, 1, 0);
	glScaled(1.0, 0.1, 0.1);
	glutSolidSphere(5, 5, 5);

	glPopMatrix();
}

Gundam::Gundam(status* in) : Graphic(in) {}
Gundam::~Gundam() {}
void Gundam::draw() {//
	glPushMatrix(); {
		glTranslated(0, (st->ysize) / 2, 0); // move to the Y-axis center of robot
		glRotated(90.0, 0, 1, 0); // rotate the robot proper way (following mouse mothion command)
		draw_body();
	}glPopMatrix();
}
void Gundam::draw_body() {//
	glPushMatrix(); {
		draw_head();
		draw_left_upper_arm();
		draw_right_upper_arm(45, 45);
		draw_left_upper_leg();
		draw_right_upper_leg();
		glScaled(0.7, 1.0, (st->zsize) / (st->ysize) * 5 / 4); // -- rescale body
		glTranslated(0, (st->ysize) / 10, 0); // move to the Y-axis center of body
		glColor3f(1.0, 1.0, 1.0);// body color : white
		glutSolidCube((st->ysize) / 5 * 2); // draw body
	}glPopMatrix();
}
void Gundam::draw_head(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, (st->ysize) / 5 * 2, 0); // move to the Y-axis center of head
		glRotated(yangle, 0, 0, 1);
		glScaled(1.0, 1.0, (st->zsize) / (st->ysize) * 5 / 3); // -- rescale head
		glColor3f(0.0, 0.0, 1.0); // head color : blue
		glutSolidCube((st->ysize) / 5); // draw head
	}glPopMatrix();
}
void Gundam::draw_left_upper_arm(double u_yangle,double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
		glTranslated(0, (st->ysize) / 10 * 3, 0); // move to the Y-axis center of upper arm
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
		draw_left_lower_arm(l_angle);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
	}glPopMatrix();
}
void Gundam::draw_right_upper_arm(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
		glTranslated(0, (st->ysize) / 10 * 3, 0); // move to the Y-axis center of upper arm
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
		draw_right_lower_arm(l_angle);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
	}glPopMatrix();
}
void Gundam::draw_left_upper_leg(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of upper right leg
		glTranslated(0, (st->ysize) / 5, 0); //move to the Y-axis center of upper legs
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 5*2, 0); //move to the Y-axis center of upper legs
		draw_left_lower_leg(l_angle);
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube((st->ysize) / 5); // draw upper right leg
	}glPopMatrix();
}
void Gundam::draw_right_upper_leg(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of upper right leg
		glTranslated(0, -(st->ysize) / 5 * 2, 0); //move to the Y-axis center of upper legs
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, (st->ysize) / 5, 0); //move to the Y-axis center of upper legs
		draw_right_lower_leg(l_angle);
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
		glColor3f(0.0, 0.0, 1.0);
		glutSolidCube((st->ysize) / 5); // draw upper right leg
	}glPopMatrix();
}
void Gundam::draw_left_lower_arm(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
	}glPopMatrix();
}
void Gundam::draw_right_lower_arm(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
	}glPopMatrix();
}
void Gundam::draw_left_lower_leg(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower left leg
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube((st->ysize) / 5); // draw lower left leg
	}glPopMatrix();
}
void Gundam::draw_right_lower_leg(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower right leg
		glColor3f(1.0, 1.0, 1.0);
		glutSolidCube((st->ysize) / 5); // draw lower right leg
	}glPopMatrix();
}


Zaku_Graphic::Zaku_Graphic(status* in) : Graphic(in) {}
Zaku_Graphic::~Zaku_Graphic() {}

void Zaku_Graphic::draw() {//
	glPushMatrix(); {
		glTranslated(st->x, st->y + (st->ysize) / 2, -st->z); // move to the Y-axis center of robot
		glRotated(-st->degree + 90, 0, 1, 0); // rotate the robot proper way (following mouse mothion command)
		draw_body();
	}glPopMatrix();
}
void Zaku_Graphic::draw_body() {//
	glPushMatrix(); {
		draw_head();
		draw_left_upper_arm();
		draw_right_upper_arm(45, 45);
		draw_left_upper_leg();
		draw_right_upper_leg();
		glScaled(0.7, 1.0, (st->zsize) / (st->ysize) * 5 / 4); // -- rescale body
		glTranslated(0, (st->ysize) / 10, 0); // move to the Y-axis center of body
		glColor3f(0.0, 0.0, 0.0);// body color : white
		glutSolidCube((st->ysize) / 5 * 2); // draw body
	}glPopMatrix();
}
void Zaku_Graphic::draw_head(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, (st->ysize) / 5 * 2, 0); // move to the Y-axis center of head
		glRotated(yangle, 0, 0, 1);
		glScaled(1.0, 1.0, (st->zsize) / (st->ysize) * 5 / 3); // -- rescale head
		glColor3f(1.0, 0.0, 0.0); // head color : blue
		glutSolidCube((st->ysize) / 5); // draw head
	}glPopMatrix();
}
void Zaku_Graphic::draw_left_upper_arm(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, -(st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
		glTranslated(0, (st->ysize) / 10 * 3, 0); // move to the Y-axis center of upper arm
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
		draw_left_lower_arm(l_angle);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
	}glPopMatrix();
}
void Zaku_Graphic::draw_right_upper_arm(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, (st->zsize) / 8 * 3); // move to the Z-axis center of left upper arm
		glTranslated(0, (st->ysize) / 10 * 3, 0); // move to the Y-axis center of upper arm
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0); // move to the Y-axis center of upper arm
		draw_right_lower_arm(l_angle);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left upper arm
	}glPopMatrix();
}
void Zaku_Graphic::draw_left_upper_leg(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, -(st->zsize) / 8); // move to the Z-axis center of upper right leg
		glTranslated(0, (st->ysize) / 5, 0); //move to the Y-axis center of upper legs
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 5 * 2, 0); //move to the Y-axis center of upper legs
		draw_left_lower_leg(l_angle);
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 5); // draw upper right leg
	}glPopMatrix();
}
void Zaku_Graphic::draw_right_upper_leg(double u_yangle, double l_angle) {//
	glPushMatrix(); {
		glTranslated(0, 0, (st->zsize) / 8); // move to the Z-axis center of upper right leg
		glTranslated(0, -(st->ysize) / 5 * 2, 0); //move to the Y-axis center of upper legs
		glRotated(u_yangle, 0, 0, 1);
		glTranslated(0, (st->ysize) / 5, 0); //move to the Y-axis center of upper legs
		draw_right_lower_leg(l_angle);
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale upper right leg
		glColor3f(1.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 5); // draw upper right leg
	}glPopMatrix();
}
void Zaku_Graphic::draw_left_lower_arm(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(0.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
	}glPopMatrix();
}
void Zaku_Graphic::draw_right_lower_arm(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 20 * 3, 0);
		glScaled((st->zsize) / (st->ysize) / 6 * 5, 1.0, (st->zsize) / (st->ysize) / 6 * 5); // -- rescale left upper arm
		glColor3f(0.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 10 * 3); // draw left lower arm
	}glPopMatrix();
}
void Zaku_Graphic::draw_left_lower_leg(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower left leg
		glColor3f(0.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 5); // draw lower left leg
	}glPopMatrix();
}
void Zaku_Graphic::draw_right_lower_leg(double yangle) {//
	glPushMatrix(); {
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glRotated(yangle, 0, 0, 1);
		glTranslated(0, -(st->ysize) / 10, 0); // move to the Y-axis center of lower legs
		glScaled((st->zsize) / (st->ysize) / 4 * 5, 1.0, (st->zsize) / (st->ysize) / 4 * 5); // -- rescale lower right leg
		glColor3f(0.0, 0.0, 0.0);
		glutSolidCube((st->ysize) / 5); // draw lower right leg
	}glPopMatrix();
}

Zaku_Dead_Particle::Zaku_Dead_Particle(status*in) : Graphic(in) {
	for (int i = 0; i < 100; i++) {
		particle[i].vectorX = (double)(rand() % 10 - 5)/10;
		particle[i].vectorY = (double)(rand() % 10 - 5)/10;
		particle[i].vectorZ = (double)(rand() % 10 - 5)/10;
		particle[i].x = st->x + particle[i].vectorX;
		particle[i].y = st->y + particle[i].vectorY;
		particle[i].y = st->z + particle[i].vectorZ;
	}
}
Zaku_Dead_Particle::~Zaku_Dead_Particle() {}

void Zaku_Dead_Particle::Update() {
	for (int i = 0; i < 100; i++) {
		particle[i].x += particle[i].vectorX;
		particle[i].y += particle[i].vectorY;
		particle[i].z += particle[i].vectorZ;
	}
}
void Zaku_Dead_Particle::draw() {
	for (int i = 0; i < 100; i++) {
		glPushMatrix(); {
			glColor3f(1.0, 1.0, 0.0);
			glTranslated(particle[i].x, particle[i].y, particle[i].z);
			glutSolidCube(0.2);
		}glPopMatrix();
	}
}

Jump_Particle::Jump_Particle(status*in) : Graphic(in) {
	for (int i = 0; i < 100; i++) {
		particle[i].vectorX = (double)(rand() % 10 - 5) / 10;
		particle[i].vectorY = (double)(rand() % 10);
		particle[i].vectorZ = (double)(rand() % 10 - 5) / 10;
		particle[i].x = st->x + particle[i].vectorX;
		particle[i].y = st->y + particle[i].vectorY;
		particle[i].y = st->z + particle[i].vectorZ;
	}
}
Jump_Particle::~Jump_Particle() {}

void Jump_Particle::Update() {
	for (int i = 0; i < 100; i++) {
		particle[i].x += particle[i].vectorX;
		particle[i].y += particle[i].vectorY;
		particle[i].z += particle[i].vectorZ;
	}
}
void Jump_Particle::draw() {
	for (int i = 0; i < 100; i++) {
		glPushMatrix(); {
			glColor3f(1.0, 1.0, 0.0);
			glTranslated(particle[i].x, particle[i].y, particle[i].z);
			glutSolidCube(0.2);
		}glPopMatrix();
	}
}