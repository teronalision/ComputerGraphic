#include "Physic.h"
#include "Define.h"


Physic::Physic(status* in)
{
	st = in;
	speed = 2;
}
Physic::~Physic()
{
}

void Physic::PhyUpdate(){
	status& s = *st;

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
	s.x += vx*speed*cos(s.degree*R);
	s.z += vx*speed*sin(s.degree*R);


	double brake = 0.05;//¸¶Âû
	if (vx > 0) vx = fmax(vx - brake, 0);
	else		vx = fmin(vx + brake, 0);
	if (vz > 0) vz = fmax(vz - brake, 0);
	else		vz = fmin(vz + brake, 0);

}