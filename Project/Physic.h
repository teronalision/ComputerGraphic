#include "Define.h"
#pragma once
class Physic
{
public:
	status* st;
	Physic(status* in);
	~Physic();
	void PhyUpdate();
};

