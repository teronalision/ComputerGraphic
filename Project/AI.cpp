#include "AI.h"



AI::AI()
{
	timer = 0;
}


AI::~AI()
{
}

zakubrain::zakubrain(Physic* in):st(in){
}

void zakubrain::AIupdate(Physic taget) {
	timer++;
	if (timer < FPS)
		return;


	int dx = st->st->x - taget.st->x;
	int dz = st->st->z - taget.st->z;
	if (dx*dx + dz*dz < SERCH_LEN*SERCH_LEN) {
		if (dx*dx + dz*dz > FIRE_LEN*FIRE_LEN) {
			st->st->degree = -90 + atan2(-dz, dx) / 3.14 * 180;
			st->vx = 0;
			st->vz = 1;
			std::cout << "Find!! " << std::endl;
		}
		else {
			st->st->degree = -90 + atan2(-dz, dx) / 3.14 * 180;
			st->vz = 0;
			st->vx = 1 + (rand() % 2) * 2;
			std::cout << "Fire!! " << std::endl;
		}
		timer = 0;
	}
	else {
		st->vz = 0;
		st->vx = 0;
	}
}
