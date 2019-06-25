#include <iostream>
#include <GL/glut.h>
#include "zombie.h"
#include "grid.h"
#define PI 3.141592

// zombie parameter 없앰
//zombie의 변수 pos,color,dir 포인터 사용하지 않음.
Zombie::Zombie() {
	k = 2;
	life = 1;
}

float Zombie::getX() const {
	return pos[0];
}

float Zombie::getY() const {
	return pos[1];
}

int Zombie::getDirection() const {
	return dir;
}

void Zombie::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}

void Zombie::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Zombie::setDirection(float d) {
	dir = d;
}

void Zombie::draw() const {
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	for (int counter = 0; counter < 4; counter++) {
		glVertex2f(pos[0] + 0.5*cos((PI / 4) + (PI * counter / 2)), pos[1] + 0.5*sin((PI / 4) + (PI * counter / 2)));
	}
	glEnd();
}
// Zombie::set 추가
void Zombie::initset() {
	pos[0] = (float)(rand() % 41);
	pos[1] = (float)(rand() % 41);
	color[0] = (float)(rand() % 100) / 100;
	color[1] = (float)(rand() % 100) / 100;
	color[2] = (float)(rand() % 100) / 100;
	dir = ((int)(rand() % 4) + 1) * 2;
}

void Zombie::randdir() {
	dir = ((int)(rand() % 4) + 1) * 2;
}

void Zombie::zombieidle(){

	randdir();
	if (dir == 4) {
		 setDirection(4);
		 if (getX() - 0.5 > 0) {
			 setPos(getX() - 0.5 / k, getY());
		 }
	}
	else if (dir == 6) {
		setDirection(6);
		if (getX() + 0.5 < 40) {
			setPos(getX() + 0.5 / k, getY());
		}
	}
	else if (dir == 8) {
		setDirection(8);
		if (getY() + 0.5 < 40) {
			setPos(getX(), getY() + 0.5 / k);
		}
	}
	else if (dir == 2) {
		setDirection(2);
		if (getY() - 0.5 > 0) {
			setPos(getX(), getY() - 0.5 / k);
		}
	}
}

void Zombie::stop() {
	dir = 0;
}

void Zombie::setK(float speed) {
	k = speed;
}