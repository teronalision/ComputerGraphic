#pragma once
#include "Graphic.h"
#include "AI.h"

enum _name
{
	gundam,zaku,zaku_a,bullet,bullet_z,paticle
};
enum _hp
{
	hp_g = 20, hp_z = 2
};
enum _magazin
{
	ma_g = 10, ma_z = 3
};

class Object {
public:
	int ID;
	_name NAME;

	int magazin;
	status myS;
	Graphic* myG;
	Physic* myP;
	AI* myA;
	Object(int id, _name name);
	virtual void update() = 0;
	bool checkName(_name name);
	virtual bool fire();
	virtual bool Kill();
};

class G :public Object {
public:
	G();
	int reload_timer;
	int delay;
	void update();
	bool fire();
};

class Zaku :public Object {
public:
	int reload_timer;
	int delay;
	Zaku(int id);
	Zaku(int id, int x, int y, int z, double d);
	void update();
	bool fire();
	bool Kill();
};

class Bullet :public Object {
public:
	Bullet(int id, int x,int y, int z, double d);
	void update();
};

class Paticle :public Object {
public:
	int Dcount;
	Paticle(int id, int x,int y, int z);
	void update();
};

static G* hero;

class que {
public:
	struct node {
		Object* data = NULL;
		node* next = NULL;
	};
	static void push_q(_name, int x, int y, int z, int d=0);
	static Object* pop_q();
};
static que::node* head = NULL;