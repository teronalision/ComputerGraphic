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
	

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
	s.x += vx*speed*cos(s.degree*R);
	s.z += vx*speed*sin(s.degree*R);
	s.y += vy;

	if (s.y <= 0) {
		s.y = 0;
		vy = 0;
	}
	else
		vy -= gravity;

	
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