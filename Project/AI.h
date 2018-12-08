#pragma once
#include "Physic.h"

#define SERCH_LEN 200
#define FIRE_LEN 50


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