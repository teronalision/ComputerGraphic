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

class Temp_Robot : public Graphic {
public:
	Temp_Robot(status*in);
	~Temp_Robot();

	void draw();
};

class Field : public Graphic {
public:
	Field(status*in);
	~Field();

	void draw();
};