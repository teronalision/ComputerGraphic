#pragma once
#include <gl\freeglut.h>



class Graphic
{
public:
	Graphic();
	~Graphic();

	virtual void draw() {}
};

class Box :private Graphic {
public:
	Box();
	~Box();

	void draw();

};