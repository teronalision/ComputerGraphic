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
	G(int x, int z);
};

class Zaku :public Object {
	Zaku(int x, int z);
};