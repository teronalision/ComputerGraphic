#include "Physic.h"
#include "Define.h"


Physic::Physic(status* in)
{
	st = in;
	speed = 5;
	magazin = 0;
	timer = -1;
}
Physic::~Physic()
{
}

bool Physic::is_fire() {
	if (magazin > 0) {
		magazin -= 1;
		return true;
	}
	else {
		if (timer == -1) {
			timer = 0;
			std::cout<<"장전시작"<<std::endl;
		}
		return false;
	}
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

Unit::Unit(status* in) :Physic(in) {
}
void Unit::PhyUpdate(){
	status& s = *st;
	

	s.x -= vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
	s.x += vx*speed*cos(s.degree*R);
	s.z += vx*speed*sin(s.degree*R);
	s.y += vy;
	
	s.x = clamp(s.x);
	s.z = clamp(s.z);

	double tx = double(int(s.x) % 10) / 10.0;
	double tz = double(int(s.z) % 10) / 10.0;

	int floor = (1 - tx)*(1 - tz)*field[int(s.z) / 10][int(s.x) / 10] + (1 - tx)*tz*field[int(s.z) / 10 + 1][int(s.x) / 10]
		+ tx*(1 - tz)*field[int(s.z) / 10][int(s.x) / 10 + 1] + tx*tz*field[int(s.z) / 10 + 1][int(s.x) / 10 + 1];
	if (s.y <= floor) {
		s.y = floor;
		vy = 0;
		std::cout << "바닥 충돌 :" <<s.x<<"," << s.y << "," << s.z<<std::endl;
	}
	else
		vy -= gravity;


	//장전
	if (timer > 3 * 30) {
		timer = -1;
		magazin = 10;
		std::cout << "재장전 완료" << std::endl;
	}
	else if (timer > -1) {
		timer++;
	}
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

double clamp(double n) {
	if (n < 1)
		return 1;
	if (n > 1000 -1)
		return 1000 -1;
	return n;
}
bool is_crash(status a, status b) {

	//x축
	if (a.x + a.xsize < b.x - b.xsize || a.x - a.xsize > b.x + b.xsize)
		return false;
	//y축
	if (a.y + a.ysize < b.y - b.ysize || a.y - a.ysize > b.y + b.ysize)
		return false;
	//z축
	if (a.z + a.zsize < b.z - b.zsize || a.z - a.zsize > b.z + b.zsize)
		return false;

	return true;
}

void knockback(Physic taget, Physic s) {
	double power = 0.3;

	taget.vx += s.vx*power;
	taget.vy += s.vy*power;
	taget.vz += s.vz*power;
}