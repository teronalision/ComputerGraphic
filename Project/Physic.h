#pragma once
#include "Define.h"

#define brake 0.1
#define gravity 0.6

static int field[101][101];

class Physic
{
public:
	status* st;
	double vx, vy, vz;
	double speed;
	double jump_count;
	int magazin;
	int timer;
	Physic(status* in);
	~Physic();
	virtual void PhyUpdate();
	bool is_fire();	//ÃÑ ½ò¼öÀÖ´ÂÁö
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

bool is_crash(status a, status b);//AABB Ãæµ¹Ã¼Å©
void knockback(Physic taget, Physic s);//³Ë¹é