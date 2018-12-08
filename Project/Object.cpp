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

bool Object::Kill() { return true; }


G::G() :Object(0, gundam) {
	myS.set_position(500, 20, 500);
	myS.degree = 0;
	myS.hp = hp_g;
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Unit(&myS);
	myP->magazin = 10;

	hero = this;
}
void G::update() {
	myP->PhyUpdate();
}

Zaku::Zaku(int id) :Object(id, zaku) {
	int r = rand() % 360;
	myS.set_position(450 * sin(r*R) + 500, 100, 450 * cos(r*R) + 500);
	myS.degree = r + 180;
	myS.hp = hp_z;
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);
	myA = new zakubrain(*myP);

	std::cout << "new zaku random (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}
Zaku::Zaku(int id, int x, int y, int z, double d):Object(id, zaku) {
	myS.set_position(x, 0, z);
	myS.hp = hp_z;
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);

	std::cout << "new zaku select (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}
void Zaku::update() {
	myP->PhyUpdate();
	myA->AIupdate(*hero->myP);
}
bool Zaku::Kill() {
	myS.live = true;
	NAME = paticle;
	delete myP;
	myP = new Paticlep(&myS);
	delete myG;
	myG = new Box(&myS);

	return false;
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
}

Paticle::Paticle(int id, int x, int y, int z):Object(id, paticle) {
	myS.set_position(x, y, z);
	myS.set_size(1,1,1);
	myP = new Paticlep(&myS);
	myG = new Box(&myS);
}