#pragma once
#include "Object.h"

#define OBJMAX 100



class World
{
public:
	int field[101][101];
	Object* objects[OBJMAX];

	World();
	~World();
	void worlddraw();
	void worldupdate();
};
