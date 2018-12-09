#pragma once
#include <gl\freeglut.h>
#include "Define.h"

#define GUNDAM_HEIGHT 2
#define Particle_MAX 20
#define JumpParticle_MAX 10

typedef struct PARTICLE {
	double x, y, z;
	double vectorX, vectorY, vectorZ;
} Particle;

class Graphic
{
public:
	status* st;
	status pi[Particle_MAX];
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

class Zaku_Dead_Particle : public Graphic {
public:
	Zaku_Dead_Particle(status*in);
	~Zaku_Dead_Particle();
	void draw();
};

class Jump_Particle : public Graphic {
public:
	Jump_Particle(status*in);
	~Jump_Particle();

	void draw();
};