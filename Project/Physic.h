#include "Define.h"
#pragma once

#define brake 0.1
#define gravity 0.6

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

bool is_crash(status a, status b);//AABB 충돌체크
void knockback(Physic taget, Physic s);//넉백