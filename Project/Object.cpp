#include "Object.h"


Object::Object() {
	myG, myP = NULL;
}

G::G(int x, int z) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Gundamp(&myS);
}

Zaku::Zaku(int x, int z) {
	myS.set_position(x, 0, z);
	myS.set_size(1, 2, 1);
	myG = new Gundam(&myS);
	myP = new Physic(&myS);

	std::cout << "磊捻 积己" << std::endl;
}

Bullet::Bullet(int x,int y, int z,double d) {
	myS.set_position(x, y, z);
	myS.degree = d;
	myS.set_size(50, 50, 50);
	myG = new Box(&myS);
	myP = new Bullp(&myS);

	std::cout << "醚舅 积己" << std::endl;
}