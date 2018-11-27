#pragma once
#include <gl\freeglut.h>
#include "Define.h"


class Graphic
{
public:
	Graphic();
	~Graphic();

	virtual void draw(status s) = 0;
};

class Box :public Graphic {
public:
	Box();
	~Box();

	void draw(status s);

};