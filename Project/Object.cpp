#include "Object.h"


Object::Object(int id, _name name) {
	ID = id;
	NAME = name;

	myG, myP = NULL;
}
bool Object::checkName(_name n) {
	if (NAME == n)
		return true;
	else
		return false;
}

void Object::Kill() {}


G::G() :Object(0, gundam) {
	myS.set_position(500, 10, 500);
	myS.degree = 0;
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Unit(&myS);
	myP->magazin = 10;
}

Zaku::Zaku(int id) :Object(id, zaku) {
	int r = rand() % 360;
	myS.set_position(450 * sin(r*R) + 500, 100, 450 * cos(r*R) + 500);
	myS.degree = r + 180;
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);

	std::cout << "ÀÚÄí ·£´ý»ý¼º (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}
Zaku::Zaku(int id, int x, int y, int z, double d):Object(id, zaku) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Unit(&myS);

	std::cout << "ÀÚÄí ÁöÁ¤»ý¼º (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}

Bullet::Bullet(int id, int x,int y, int z,double d):Object(id, bullet) {
	myS.set_position(x, y, z);
	myS.degree = d;
	myS.set_size(0.5, 0.5, 0.5);
	myG = new Bullet_Graphic(&myS);
	myP = new Bullp(&myS);

	std::cout << "ÃÑ¾Ë »ý¼º" << std::endl;
}