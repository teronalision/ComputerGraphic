#include "AI.h"



AI::AI()
{
}


AI::~AI()
{
}

zakubrain::zakubrain(Physic& in):st(in){
}

void zakubrain::AIupdate(Physic taget) {
	int dx = st.st->x - taget.st->x;
	int dz = st.st->z - taget.st->z;
	if (dx*dx + dz*dz < SERCH_LEN*SERCH_LEN) {
		st.st->degree = atan2(dz, dx)/-R;
	}
}
