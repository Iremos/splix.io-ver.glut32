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
	void initset(); //initset으로 초기의 위치, 색, 방향 모두 랜덤으로 지정해준다.
	void randdir(); //direction을 랜덤으로 지정한다.
	void zombieidle(); //idle 안에서 좀비의 위치를 업데이트할 함수
	void stop();
	void setK(float speed);
	//dir, k 를 public 으로 바꿈
	int dir;
	int k;
	int life;
private:
	float pos[2];
	float color[3];


};