#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

zakubrain::zakubrain(Physic* in):st(in){
}

void zakubrain::AIupdate(Physic taget) {
	int dx = st->st->x - taget.st->x;
	int dz = st->st->z - taget.st->z;
	if (dx*dx + dz*dz < SERCH_LEN*SERCH_LEN) {
		st->st->degree = -90 + atan2(-dz, dx) / 3.14 * 180;
		st->vz = 1;
		std::cout << "Find!! " << st->st->degree << std::endl;
	}
	else
		st->vz = 0;
}
