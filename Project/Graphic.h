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
	Box();
	~Box();

	void draw();

};