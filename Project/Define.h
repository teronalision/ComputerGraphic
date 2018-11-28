#pragma once

#define FPS 30
#define WIN_H 400.0
#define WIN_W 500.0
#define DIS 500


struct status
{
	int x, y, z;
	int degree;
	int xsize, ysize, zsize;
};
struct Camera {
	double eyex, eyey, eyez;
	double centerx, centery, centerz;
	double upx, upy, upz;
};
double zoom = 10.0;