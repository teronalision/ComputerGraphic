#include "Object.h"


Object::Object() {
	myG, myP = NULL;
}

G::G(int x, int z) {
	myS.set_position(x, 0, z);
	myG = new Gundam(&myS);
	myP = new Gundamp(&myS);
}

Zaku::Zaku(int x, int z) {
	myS.set_position(x, 0, z);
	myS.set_size(300, 300, 300);
	myG = new Gundam(&myS);
	myP = new Physic(&myS);
}

Bullet::Bullet(int x, int z,double d) {
	myS.set_position(x, 0, z);
	myS.degree = d;
	myS.set_size(50, 50, 50);
	myG = new Gundam(&myS);
	myP = new Bullp(&myS);
}