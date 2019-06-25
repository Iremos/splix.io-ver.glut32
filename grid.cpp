#include <iostream>
#include <GL/glut.h>
#include "grid.h"
#define PI 3.141592

Grid::Grid() {
	pos[0] = 0;
	pos[1] = 0; 
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	state = 0;
	trace = 0;

}

Grid::Grid(float x, float y) {
	std::cout << "Constructor 0" << std::endl;
	pos[0] = x;
	pos[1] = y;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	state = 0;
	trace = 0;

}

float Grid::getX() const {
	return pos[0];
}

float Grid::getY() const {
	return pos[1];
}

float Grid::getR() const {
	return color[0];
}

float Grid::getG() const {
	return color[1];
}

float Grid::getB() const {
	return color[2];
}

int Grid::getState() const {
	return state;
}

int Grid::getTrace() const {
	return trace;
}

void Grid::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}

void Grid::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Grid::setState(int s) {
	state = s;
	if (state == 1) {
		setColor(0.6,0.6,0.2);
	}
}

void Grid::setTrace(int t) {
	trace = t;

}

void Grid::draw() const {
	float k = 0.6;
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	for (int counter = 0; counter < 4; counter++) {
		glVertex2f(pos[0] + k*cos((PI / 4) + (PI * counter / 2)), pos[1] + k*sin((PI / 4) + (PI * counter / 2)));
	}
	glEnd();
	if (trace == 1) { //traceÀÏ °æ¿ì draw points
		glColor3f(0.7, 0.7, 0.3);
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glVertex2f(pos[0], pos[1]);
		glEnd();
	}
}

