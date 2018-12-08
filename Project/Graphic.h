#pragma once
#include <gl\freeglut.h>
#include "Define.h"

#define GUNDAM_HEIGHT 2

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

class Bullet_Graphic : public Graphic {
public:
	Bullet_Graphic(status*in);
	~Bullet_Graphic();

	void draw();
};

class Gundam : public Graphic {
public:
	Gundam(status*in);
	~Gundam();

	void draw();
	void draw_body();
	void draw_head(double yangle = 0);
	void draw_left_upper_arm(double u_yangle = 0,double l_yangle = 0);
	void draw_right_upper_arm(double u_yangle = 0, double l_yangle = 0);
	void draw_left_upper_leg(double u_yangle = 0, double l_yangle = 0);
	void draw_right_upper_leg(double u_yangle = 0,double l_yangle = 0);
	void draw_left_lower_arm(double yangle = 0);
	void draw_right_lower_arm(double yangle = 0);
	void draw_left_lower_leg(double yangle = 0);
	void draw_right_lower_leg(double yangle = 0);
};

class Zaku_Graphic : public Graphic {
public:
	Zaku_Graphic(status*in);
	~Zaku_Graphic();

	void draw();
	void draw_body();
	void draw_head(double yangle = 0);
	void draw_left_upper_arm(double u_yangle = 0, double l_yangle = 0);
	void draw_right_upper_arm(double u_yangle = 0, double l_yangle = 0);
	void draw_left_upper_leg(double u_yangle = 0, double l_yangle = 0);
	void draw_right_upper_leg(double u_yangle = 0, double l_yangle = 0);
	void draw_left_lower_arm(double yangle = 0);
	void draw_right_lower_arm(double yangle = 0);
	void draw_left_lower_leg(double yangle = 0);
	void draw_right_lower_leg(double yangle = 0);

};

class GUI {
public:
	GUI();
	~GUI();
	void draw();
};

class Field : public Graphic {
public:
	Field(status*in);
	~Field();

	void draw();
};