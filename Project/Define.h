#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
#define FPS 30
#define WIN_H 400.0
#define WIN_W 500.0
#define DIS 500
#define R 3.14/180


struct status
{
	double x, y, z;
	double degree;
	double xsize, ysize, zsize;
	bool live = true;

	void set_position(int ix, int iy, int iz) {
		x = ix;
		y = iy;
		z = iz;
	}
	void set_size(int ix, int iy, int iz) {
		xsize = ix;
		ysize = iy;
		zsize = iz;
	}
};
struct Camera {
	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;
};
