#pragma once
#include <iostream>
#include <math.h>
#include <time.h>
#define FPS 30
#define WIN_H 400.0
#define WIN_W 500.0
#define DIS 500
#define R 3.14/180
#define RESOLUTION 500

struct status
{
	double x, y, z;
	double degree;
	double xsize, ysize, zsize;

	int hp =10;
	bool live = true;

	void set_position(double ix, double iy, double iz) {
		x = ix;
		y = iy;
		z = iz;
	}
	void set_size(double ix, double iy, double iz) {
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
