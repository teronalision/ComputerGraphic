#include "Define.h"
#pragma once
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

