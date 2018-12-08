#pragma once
#include "Graphic.h"
#include "AI.h"

enum _name
{
	gundam,zaku,bullet,paticle
};
enum _hp
{
	hp_g = 20, hp_z = 2
};

class Object {
public:
	int ID;
	_name NAME;

	status myS;
	Graphic* myG;
	Physic* myP;
	AI* myA;
	Object(int id, _name name);
	virtual void update() = 0;
	bool checkName(_name name);
	virtual bool Kill();
};

class G :public Object {
public:
	G();
	void update();
};

class Zaku :public Object {
public:
	Zaku(int id);
	Zaku(int id, int x, int y, int z, double d);
	void update();
	bool Kill();
};

class Bullet :public Object {
public:
	Bullet(int id, int x,int y, int z, double d);
	void update();
};

class Paticle :public Object {
public:
	Paticle(int id, int x,int y, int z);
};

static G* hero;