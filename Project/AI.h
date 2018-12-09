#pragma once
#include "Physic.h"

#define SERCH_LEN 100
#define FIRE_LEN 30


class AI
{
public:
	int timer;
	bool in_fire_range;
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
class zakuAttacker :public AI {
public:
	Physic* st;
	zakuAttacker(Physic* in);
	void AIupdate(Physic taget);
};