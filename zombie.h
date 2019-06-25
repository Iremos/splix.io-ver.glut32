#pragma once
#include <iostream>
#include <GL/glut.h>

class Zombie {
public:
	Zombie();

	float getX() const;
	float getY() const;
	int getDirection() const;
	void setPos(float x, float y);
	void setColor(float r, float g, float b);
	void setDirection(float d);
	void draw() const;
	void initset(); //initset���� �ʱ��� ��ġ, ��, ���� ��� �������� �������ش�.
	void randdir(); //direction�� �������� �����Ѵ�.
	void zombieidle(); //idle �ȿ��� ������ ��ġ�� ������Ʈ�� �Լ�
	void stop();
	void setK(float speed);
	//dir, k �� public ���� �ٲ�
	int dir;
	int k;
	int life;
private:
	float pos[2];
	float color[3];


};