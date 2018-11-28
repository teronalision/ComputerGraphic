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
	status& s = *st;

	s.x += s.speed*sin(s.degree);
	s.z += s.speed*cos(s.degree);


}