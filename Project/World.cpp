#define _CRT_SECURE_NO_WARNINGS
#include "World.h"

GLubyte* Loadbmp(const char* filename, BITMAPINFO** info) {
	FILE *f;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((f = fopen(filename, "rb")) == NULL)
		return NULL;
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, f) < 1) {
		fclose(f);
		return NULL;
	}
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(f);
		exit(0);
		return NULL;
	}
	if (fread(*info, 1, infosize, f) < (unsigned int)infosize) {
		free(*info);
		fclose(f);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 * abs((*info)->bmiHeader.biHeight);

	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(f);
		return NULL;
	}
	fread(bits, 1, bitsize, f);
	fclose(f);
	return bits;
}
World::World()
{
	srand(time(NULL));

	GLubyte *map;
	BITMAPINFO *info;
	map = Loadbmp("map.bmp", &info);
	
	
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			field[i][j] = map[i*100+j];
		}
	}
	objects[0] = new G();

}


World::~World()
{
}


void World::worlddraw() {
	
	gluLookAt(2*GUNDAM_HEIGHT*cos((objects[0]->myS.degree + 90.0)*R), GUNDAM_HEIGHT, 2*GUNDAM_HEIGHT*sin((objects[0]->myS.degree + 90.0)*R), 0, 1, 0, 0, 1, 0);

	objects[0]->myG->draw();
	glTranslated(-objects[0]->myS.x, -objects[0]->myS.y, -objects[0]->myS.z);

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(0.5,0.5,0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 10, z = j * 10;
			glColor3f(0.5,0.5,i/100.0);
			glVertex3i(x, field[j+1][i], z);
			glVertex3i(x, field[j][i], z + 10);
			glVertex3i(x+10, field[j][i+1], z+10);
			glVertex3i(x + 10, field[j+1][i+1],z);
		}
	}
	glEnd();
	glPopMatrix();
	
	
	/*glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			int x = i * 100, z = -j * 100;
			glColor3f(0.5, 0.5, i / 100.0);
			glVertex3i(x, field[j + 1][i]+1, z);
			glVertex3i(x, field[j][i]+1, z + 100);
			glVertex3i(x + 100, field[j][i + 1]+1, z + 100);
			glVertex3i(x + 100, field[j + 1][i + 1]+1, z);
		}
	}
	glEnd();
	glPopMatrix();*/

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] != NULL)
			objects[i]->myG->draw();
	}
}

void World::worldupdate() {
	for (int i = 0; i < OBJMAX; i++) {
		for (int j = 1; j < OBJMAX; j++) {//�浹�˻�
			if (objects[i] == NULL || objects[j] == NULL)
				continue;

			if (objects[i]->checkName(bullet) && objects[j]->checkName(zaku)
				&& is_crash(objects[i]->myS, objects[j]->myS)) {
				objects[i]->myS.live = false;
				objects[j]->myS.live = false;
				std::cout << "�浹 : " << j << "����� " << i << "�Ѿ�" << std::endl;
			}
		}
	}

	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		if (objects[i]->checkName(zaku) && is_crash(objects[0]->myS, objects[i]->myS)) {
			objects[i]->myS.live = false;
			std::cout << "�浹 : �Ǵ�� " << i << "����" << std::endl;
		}
	}


	for (int i = 0; i < OBJMAX; i++) {
		if (objects[i] == NULL)
			continue;

		objects[i]->myP->PhyUpdate();

		if (objects[i]->myS.live == false) {//��ü ����
			objects[i]->Kill();
			delete objects[i];
			objects[i] = NULL;
		}
	}

	if (rand() % 100 == 0) {
		addOBJ(zaku);
	}

}

void World::addOBJ(_name o,int x, int y, int z,double d) {
	for (int i = 1; i < OBJMAX; i++) {
		if (objects[i] == NULL) {
			switch (o)
			{
			case zaku:
				objects[i] = new Zaku(i);
				break;
			case bullet:
				objects[i] = new Bullet(i,x,0, z,d);
				break;
			default:
				break;
			}
			break;
		}
	}

}