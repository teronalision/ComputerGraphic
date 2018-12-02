#pragma once
#include "Object.h"

#define OBJMAX 100



class World
{
public:
	int feild[100][100];
	Object* objects[OBJMAX];

	World();
	~World();
	void worlddraw();
	void worldupdate();
};
