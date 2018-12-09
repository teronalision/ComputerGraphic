#include "Object.h"


Object::Object(int id, _name name) {
	ID = id;
	NAME = name;

	myG, myP, myA = NULL;
}
bool Object::checkName(_name n) {
	if (NAME == n)
		return true;
	else
		return false;
}
bool Object::is_fire() { return false; }
bool Object::Kill() { return true; }


G::G() :Object(0, gundam) {
	myS.set_position(500, 20, 500);
	myS.degree = 0;
	myS.hp = hp_g;
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Unit(&myS);
	magazin = ma_g;
	reload_timer = -1;
	myP->speed = 30;
	delay = 0;

	hero = this;
}
bool G::is_fire() {
	if (delay < 0) {
		delay = FPS / 3;
		if (magazin > 0) {
			magazin -= 1;
			return true;
		}
		else {
			if (reload_timer == -1) {
				reload_timer = 0;
				std::cout << "start reload" << std::endl;
			}
			return false;
		}
	}
	return false;
}

void G::update() {
	myP->PhyUpdate();
	delay--;

	if (reload_timer > 2 * FPS) {
		reload_timer = -1;
		magazin = ma_g;
		std::cout << "reloading over" << std::endl;
	}
	else if (reload_timer > -1) {
		reload_timer++;
	}
}

Zaku::Zaku(int id) :Object(id, zaku) {
	int r = rand() % 360;
	myS.set_position(450 * sin(r*R) + 500, 100, 450 * cos(r*R) + 500);
	myS.degree = r + 180;
	myS.hp = hp_z;
	myS.set_size(2, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);
	myA = new zakubrain(myP);
	myP->speed = 10;
	magazin = ma_z;
	delay = 0;
	reload_timer = -1;

	std::cout << "new zaku random (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}
Zaku::Zaku(int id, int x, int y, int z, double d):Object(id, zaku) {
	myS.set_position(x, 0, z);
	myS.hp = hp_z;
	myS.set_size(2, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);
	myA = new zakubrain(myP);
	myP->speed = 10;
	magazin = ma_z;
	delay = 0;
	reload_timer = -1;

	std::cout << "new zaku select (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}
void Zaku::update() {
	myP->PhyUpdate();
	myA->AIupdate(*hero->myP);
	delay--;

	if (reload_timer > 2 * FPS) {
		reload_timer = -1;
		magazin = ma_z;
		std::cout << "reloading over" << std::endl;
	}
	else if (reload_timer > -1) {
		reload_timer++;
	}
}
bool Zaku::is_fire() {
	if (delay < 0) {
		delay = FPS / 3;
		if (magazin > 0) {
			magazin -= 1;
			return true;
		}
		else {
			if (reload_timer == -1) {
				reload_timer = 0;
				std::cout << "start reload" << std::endl;
			}
			return false;
		}
	}
	return false;
}

bool Zaku::Kill() {
	que::push_q(paticle,myS.x, myS.y, myS.z);

	return true;
}

Bullet::Bullet(int id, int x,int y, int z,double d):Object(id, bullet) {
	myS.set_position(x, y, z);
	myS.degree = d;
	myS.hp = 1;
	myS.set_size(0.5, 0.5, 0.5);
	myG = new Bullet_Graphic(&myS);
	myP = new Bullp(&myS);

	std::cout << "new bullet"<< std::endl;
}
void Bullet::update() {
	myP->PhyUpdate();

	if (myS.x < 0 || myS.x >1000 || myS.z < 0 || myS.z >1000)
		myS.live = false;
}

Paticle::Paticle(int id, int x, int y, int z):Object(id, paticle) {
	myS.set_position(x, y, z);
	myS.set_size(1,1,1);
	myP = new Paticlep(&myS);
	myG = new Zaku_Dead_Particle(&myS);

	std::cout << "new paticle" << std::endl;
}
void Paticle::update() {

}

void que::push_q(_name name, int x, int y, int z, int d) {
	node* t = head;
	while (t != NULL)
	{
		t = t->next;
	}
	t = new node;
	switch (name)
	{
	case zaku:
		t->data = new Zaku(-1,x,y,z,d);
		break;
	case bullet:
		t->data = new Bullet(-1,x,y,z,d);
		break;
	case paticle:
		t->data = new Paticle(-1,x,y,z);
		break;
	}
}
Object* que::pop_q() {
	if (head == NULL)
		return NULL;
	Object* r = head->data;
	node* d = head;
	head = head->next;
	delete d;
	return r;
}