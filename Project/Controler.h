#pragma once
#include "World.h"


static Object** taget = NULL;
void ctrinit(Object** t);
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseClick(int button, int state, int x, int y);
void MouseMove(int x, int y);

