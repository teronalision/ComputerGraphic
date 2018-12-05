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

class Gundamp :public Physic {
public:
	Gundamp(status* in);
	void PhyUpdate();
};

class Bullp:public Physic {
public:
	Bullp(status* in);
	void PhyUpdate();
};