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

class G :public Object {
public:
	G(int x, int z);
};

class Zaku :public Object {
public:
	Zaku(int x, int z);
};

class Bullet :public Object {
public:
	Bullet(int x, int z, double d);
};