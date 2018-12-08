#pragma once
#include "Physic.h"

#define SERCH_LEN 100


class AI
{
public:
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