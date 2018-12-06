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

class Gundam : public Graphic {
public:
	Gundam(status*in);
	~Gundam();

	void draw();
};

class Zaku_Graphic : public Graphic {
public:
	Zaku_Graphic(status*in);
	~Zaku_Graphic();
	void draw();
};

class Field : public Graphic {
public:
	Field(status*in);
	~Field();

	void draw();
};