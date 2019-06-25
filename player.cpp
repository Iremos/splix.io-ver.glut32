#include <iostream>
#include <GL/glut.h>
#include "player.h"
#define PI 3.141592


Player::Player() {
	pos[0] = 0;
	pos[1] = 0;
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	dir = 0;
}

Player::Player(float x, float y, float r, float g, float b) {
	life = 3;
	pos[0] = x;
	pos[1] = y;
	color[0] = r;
	color[1] = g;
	color[2] = b;
	dir = 0;
}

float Player::getX() const {
	return pos[0];
}

float Player::getY() const {
	return pos[1];
}

float Player::getR() const {
	return color[0];
}

float Player::getG() const {
	return color[1];
}

float Player::getB() const {
	return color[2];
}

int Player::getDirection() const {
	return dir;
}

void Player::setPos(float x, float y) {
	pos[0] = x;
	pos[1] = y;
}

void Player::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Player::setDirection(float d) {
	dir = d;
}

void Player::draw() const {
	glBegin(GL_POLYGON);
	glColor3f(color[0], color[1], color[2]);
	for (int counter = 0; counter < 4; counter++) {
		glVertex2f(pos[0] + 0.5*cos((PI / 4) + (PI * counter / 2)), pos[1] + 0.5*sin((PI / 4) + (PI * counter / 2)));
	}

	glEnd();
}