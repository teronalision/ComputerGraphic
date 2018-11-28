#pragma once
#include <math.h>
#define FPS 30
#define WIN_H 400.0
#define WIN_W 500.0
#define DIS 500
#define R 3.14/180


struct status
{
	int x, y, z;
	int degree;
	int xsize, ysize, zsize;
	double speed;
};
struct Camera {
	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;
};
