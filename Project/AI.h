#pragma once
#include "Physic.h"

#define SERCH_LEN 150
#define FIRE_LEN 30


class AI
{
public:
	int timer;
	AI();
	~AI();
	virtual void AIupdate(Physic taget) = 0;
};

class zakubrain :public AI {
public:
	Physic* st;
	zakubrain(Physic* in);
	void AIupdate(Physic taget);
};