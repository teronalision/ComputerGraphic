#pragma once
#include "Graphic.h"
#include "Physic.h"
#include "Define.h"

#define _GUNDAM 100
#define _ZAKU	101
#define _BULLET 102

enum _name
{
	gundam,zaku,bullet
};


class Object {
public:
	int ID;
	_name NAME;

	status myS;
	Graphic* myG;
	Physic* myP;

	Object(int id, _name name);
	bool checkName(_name name);
	void Kill();
};

class G :public Object {
public:

	G(int id, int x, int z);
};

class Zaku :public Object {
public:
	Zaku(int id, int x, int y, int z, double d);
};

class Bullet :public Object {
public:
	static unsigned int magarzin;
	Bullet(int id, int x,int y, int z, double d);
};