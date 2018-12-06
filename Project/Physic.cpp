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
		//std::cout << "바닥 충돌" << std::endl;
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

bool is_crash(status a, status b) {

	//x축
	if (a.x + a.xsize < b.x - b.xsize || a.x - a.xsize < b.x + b.xsize)
		return false;
	//y축
	if (a.y + a.ysize < b.y - b.ysize || a.y - a.ysize < b.y + b.ysize)
		return false;
	//z축
	if (a.z + a.zsize < b.z - b.zsize || a.z - a.zsize < b.z + b.zsize)
		return false;

	return true;
}

void knockback(Physic taget, Physic s) {
	double power = 0.3;

	taget.vx += s.vx*power;
	taget.vy += s.vy*power;
	taget.vz += s.vz*power;
}