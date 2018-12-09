#pragma once
#include "Define.h"

#define brake 0.1
#define gravity 3.0/FPS

static int field[101][101];

class Physic
{
public:
	status* st;
	double vx, vy, vz;
	double speed;
	double jump_count;
	Physic(status* in);
	~Physic();
	virtual void PhyUpdate();
};

class Unit :public Physic {
public:
	Unit(status* in);
	void PhyUpdate();
};

class Bullp:public Physic {
public:
	Bullp(status* in);
	void PhyUpdate();
};

class Paticlep:public Physic{
public:
	Paticlep(status* in);
	void PhyUpdate();
};

double clamp(double n);
bool is_crash(status a, status b);		//AABB Check
void knockback(Physic taget, Physic s);	//knockback
void loadmap(unsigned char* data);