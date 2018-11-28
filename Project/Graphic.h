#pragma once
#include <gl\freeglut.h>
#include "Define.h"


class Graphic
{
public:
	status* st;
	Graphic(status* in);
	~Graphic();

	virtual void draw() = 0;
};

class Box :public Graphic {
public:
	Box(status* in);
	~Box();

	void draw();

};