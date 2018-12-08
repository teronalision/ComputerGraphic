#include "Physic.h"

void loadmap(unsigned char* data) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			field[i][j] = data[i * 100 + j];
		}
	}
}

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
			std::cout<<"start reload"<<std::endl;
		}
		return false;
	}
}

void Physic::PhyUpdate() {
}

Unit::Unit(status* in) :Physic(in) {
}
void Unit::PhyUpdate(){
	status& s = *st;
	

	s.x += vz*speed/FPS*sin(s.degree*R);
	s.z += vz*speed/FPS*cos(s.degree*R);
	s.x += vx*speed/FPS*cos(s.degree*R);
	s.z -= vx*speed/FPS*sin(s.degree*R);
	s.y += vy;
	
	s.x = clamp(s.x);
	s.z = clamp(s.z);

	double tx = double(int(s.x) % 10) / 10.0;
	double tz = double(int(s.z) % 10) / 10.0;

	int p[4] = { field[int(s.z/10)][int(s.x/10)],field[int(s.z/10)][int(s.x/10)+1]
				,field[int(s.z/10)+1][int(s.x/10)],field[int(s.z/10)+1][int(s.x/10)+1] };

	int floor = (1 - tx)*(1 - tz)*p[0] + (1 - tx)*tz*p[2] + tx*(1 - tz)*p[1] + tx*tz*p[3];
	if (s.y <= floor) {
		s.y = floor;
		vy = 0;
		//std::cout << "바닥 충돌 :"<<s.degree<<"/" <<s.x<<"," << s.y << "," << s.z<<std::endl;
	}
	else
		vy -= gravity;


	//장전
	if (timer > 3 *FPS) {
		timer = -1;
		magazin = 10;
		std::cout << "reloading over" << std::endl;
	}
	else if (timer > -1) {
		timer++;
	}
}

Bullp::Bullp(status* in):Physic(in) {
	vz = 1;
	speed = 4;
}

void Bullp::PhyUpdate() {
	status& s = *st;

	s.x += vz*speed*sin(s.degree*R);
	s.z += vz*speed*cos(s.degree*R);
}

Paticlep::Paticlep(status* in):Physic(in) {
	deadcount = 3 * FPS;
}
void Paticlep::PhyUpdate() {
	if (--deadcount < 0)
		st->live = false;
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