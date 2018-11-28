#include "Physic.h"
#include "Define.h"


Physic::Physic(status* in)
{
	st = in;
}
Physic::~Physic()
{
}

void Physic::PhyUpdate(){
	st->vx = st->vx > 5 ? 5 : st->vx*0.7;
}