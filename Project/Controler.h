#pragma once
#include "World.h"

static World* ww = NULL;
static Object** taget = NULL;
void ctrinit(World* t);
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseClick(int button, int state, int x, int y);
void MouseMove(int x, int y);

