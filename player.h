#pragma once
#include <iostream>
#include <vector>
#include <GL/glut.h>

using namespace std;

class Player {
public:
	Player();
	Player(float x, float y, float r, float g, float b);
	float getX() const;
	float getY() const;
	float getR() const;
	float getG() const;
	float getB() const;
	int getDirection() const;
	void setPos(float x, float y);
	void setColor(float r, float g, float b);
	void setDirection(float d);
	void draw() const;

	int life;

private:
	float pos[2];
	float color[3];
	int dir;


	};