#include "Object.h"


Object::Object() {
	myG, myP = NULL;
}

void Object::Kill(){}


G::G(int x, int z) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Unit(&myS);
}

Zaku::Zaku(int x, int y, int z, double d) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Zaku_Graphic(&myS);
	myP = new Physic(&myS);

	std::cout << "���� ���� (" << myS.x<<","<< myS.y << "," <<myS.z << ")"<< std::endl;
}

Bullet::Bullet(int x,int y, int z,double d) {
	myS.set_position(x, y, z);
	myS.degree = d;
	myS.set_size(0.5, 0.5, 0.5);
	myG = new Box(&myS);
	myP = new Bullp(&myS);

	std::cout << "�Ѿ� ����" << std::endl;
}