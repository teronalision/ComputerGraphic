#pragma once
#include "Graphic.h"
#include "Physic.h"
#include "Define.h"


class Object {
public:
	status myS;
	Graphic* myG;
	Physic* myP;
	Object();
};

class World
{
public:
	int feild[100][100];
	Object objects[100];

	World();
	~World();
	void worlddraw();
	void worldupdate();
};
