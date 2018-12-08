#pragma once
#include "Object.h"

#define OBJMAX 100



class World
{
public:
	Object* objects[OBJMAX];

	World();
	~World();
	void worlddraw();
	void worldupdate();
	void addOBJ(_name o,int x=0, int y=0, int z=0, double d = 0);
};
