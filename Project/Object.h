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
