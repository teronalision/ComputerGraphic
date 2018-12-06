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

void Object::Kill(){}


G::G(int id, int x, int z):Object(id, gundam) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Unit(&myS);
}

Zaku::Zaku(int id, int x, int y, int z, double d):Object(id, zaku) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Physic(&myS);

	std::cout << "磊捻 积己 (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}

Bullet::Bullet(int id, int x,int y, int z,double d):Object(id, bullet) {
	myS.set_position(x, y, z);
	myS.degree = d;
	myS.set_size(0.5, 0.5, 0.5);
	myG = new Box(&myS);
	myP = new Bullp(&myS);

	std::cout << "醚舅 积己" << std::endl;
}