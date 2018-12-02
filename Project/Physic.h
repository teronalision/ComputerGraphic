#include "Define.h"
#pragma once

#define brake 0.05

class Physic
{
public:
	status* st;
	double vx, vz;
	double speed;
	double jump_count;
	Physic(status* in);
	~Physic();
	void PhyUpdate();
};

class Gundamp :public Physic {
public:
	double jump_count;
	Gundamp(status* in);
	void PhyUpdate();
};

class Bullp:public Physic {
public:
	Bullp(status* in);
};