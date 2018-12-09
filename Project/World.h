#pragma once
#include "Object.h"

#define OBJMAX 100


class World
{
public:
	double worldtime;
	Object* objects[OBJMAX];
	double Yaim;

	World();
	~World();
	void worlddraw();
	void worldupdate();
	void addOBJ(_name o,int x=0, int y=0, int z=0, double d = 0);
};

void GUIdraw(int hp, int bullet, World worldinfo);
void ModelInit();
void DrawSun(double x, double y, double z);
void SunLight(double x, double y, double z);