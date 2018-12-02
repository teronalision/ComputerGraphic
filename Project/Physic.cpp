#include "Physic.h"
#include "Define.h"


Physic::Physic(status* in)
{
	st = in;
	speed = 5;
}
Physic::~Physic()
{
}

void Physic::PhyUpdate() {
	status& s = *st;

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
	s.x += vx*speed*cos(s.degree*R);
	s.z += vx*speed*sin(s.degree*R);



	if (vx > 0) vx = fmax(vx - brake, 0);
	else		vx = fmin(vx + brake, 0);
	if (vz > 0) vz = fmax(vz - brake, 0);
	else		vz = fmin(vz + brake, 0);

}

Gundamp::Gundamp(status* in) :Physic(in) {
}
void Gundamp::PhyUpdate(){
	status& s = *st;
	static int real_y = s.y;
	if (jump_count > 0.5)
		s.y = real_y + (1 - jump_count)*100;
	else
		s.y = real_y + jump_count*100;
	if (jump_count > 0)
		jump_count-= 0.05;

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
	s.x += vx*speed*cos(s.degree*R);
	s.z += vx*speed*sin(s.degree*R);


	if (vx > 0) vx = fmax(vx - brake, 0);
	else		vx = fmin(vx + brake, 0);
	if (vz > 0) vz = fmax(vz - brake, 0);
	else		vz = fmin(vz + brake, 0);

}

Bullp::Bullp(status* in):Physic(in) {
	vz = -1;
	speed = 10;
}

void Bullp::PhyUpdate() {
	status& s = *st;

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
}