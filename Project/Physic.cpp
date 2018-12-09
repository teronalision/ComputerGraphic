#include "Physic.h"

void loadmap(unsigned char* data) {
	for (int i = 0; i < RESOLUTION; i++) {
		for (int j = 0; j < RESOLUTION; j++) {
			field[i][j] = data[i * RESOLUTION + j];
		}
	}
}

Physic::Physic(status* in)
{
	st = in;
	speed = 5;
}
Physic::~Physic()
{
}

void Physic::PhyUpdate() {
}

Unit::Unit(status* in) :Physic(in) {
}
void Unit::PhyUpdate(){
	status& s = *st;
	

	s.x += vz*speed/FPS*sin(s.degree*R);
	s.z += vz*speed/FPS*cos(s.degree*R);
	s.x += vx*speed/FPS*cos(s.degree*R)/2;
	s.z -= vx*speed/FPS*sin(s.degree*R)/2;
	s.y += vy;
	
	s.x = clamp(s.x);
	s.z = clamp(s.z);

	int spec = 1000 / RESOLUTION;

	double tx = (s.x - int(s.x)) /spec;
	double tz = (s.x - int(s.x)) / spec;

	int p[4] = { field[int(s.z/spec)][int(s.x/spec)],field[int(s.z/spec)][int(s.x/spec)+1]
				,field[int(s.z/spec)+1][int(s.x/spec)],field[int(s.z/spec)+1][int(s.x/spec)+1] };

	int floor = (1 - tx)*(1 - tz)*p[0] + (1 - tx)*tz*p[2] + tx*(1 - tz)*p[1] + tx*tz*p[3];
	//int floor = field[int(s.z/2)][int(s.x/2)];
	if (s.y <= floor) {
		s.y = floor;
		vy = 0;
		//std::cout << "바닥 충돌 :"<<s.degree<<"/" <<s.x<<"," << s.y << "," << s.z<<std::endl;
	}
	else
		vy<-3? -3: vy -= gravity;

	if (s.y < 37) {
		s.hp -= 1;
		std::cout << "aaaa";
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
	s.y += 2*sin(-s.ysize*R);

	int floor = field[int(s.z/2)][int(s.x/2)];
	if (s.y <= floor-3) {
		s.live = false;
		//std::cout << "under ground" <<std::endl;
	}
}

Paticlep::Paticlep(status* in):Physic(in) {
}
void Paticlep::PhyUpdate() {
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
	if (a.y + a.ysize < b.y - 1 || a.y - a.ysize > b.y + 1)
		return false;
	//z축
	if (a.z + a.zsize < b.z - b.zsize || a.z - a.zsize > b.z + b.zsize)
		return false;

	return true;
}

void knockback(Physic* taget, Physic s) {
	double power = 2;

	taget->st->x += s.vz*sin(s.st->degree*R)*power;
	taget->st->y += sin(-s.st->ysize*R)*power;
	taget->st->z += s.vz*cos(s.st->degree*R)*power;
}