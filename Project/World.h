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
	void addOBJ(name o,int x, int z, double d = 0);
};
