#include "Object.h"


Object::Object() {
	myG, myP = NULL;
}

G::G(int x, int z) {
	myS.x = x; myS.z = z;
	myG = new Gundam(&myS);
	myP = new Physic(&myS);
}

Zaku::Zaku(int x, int z) {
	myS.x = x; myS.z = z;

	myS.set_position(500, 0, 500);
	myS.set_size(300, 300, 300);
	myG = new Gundam(&myS);
	myP = new Physic(&myS);
}