#pragma once
#include <iostream>
#include <GL/glut.h>

class Grid {
public:
	Grid();
	Grid(float x, float y);
	float getX() const;
	float getY() const;
	float getR() const;
	float getG() const;
	float getB() const;
	int getState() const;
	int getTrace() const;
	void setPos(float x, float y);
	void setColor(float r, float g, float b);
	void setState(int s);
	void setTrace(int t);
	void draw() const;

private:
	float pos[2];
	float color[3];
	int state;
	int trace;
};
