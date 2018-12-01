#include "Define.h"
#pragma once
class Physic
{
public:
	status* st;
	double vx, vz;
	double speed;
	Physic(status* in);
	~Physic();
	void PhyUpdate();
};

