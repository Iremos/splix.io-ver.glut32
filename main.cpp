























































#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include "grid.h"
#include "player.h"
#include "zombie.h"
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

float speed = 0.07;
float zombiespeed = 3;
int level = 1;
int game_state = 1;
int sp_key = 0;
int zombienum = 0;
int territory = 0;
int ratio;
int kill;

//test speed;
float test1 = 0.5 - speed;
float test2 = 0.5 + speed;

//fill �� �ִٰ� ������ ������ ���� ó�� grids ��ǥ
vector<float> firstpoint;
vector<float> secondpoint;

#define WIDTH 800		
#define HEIGHT 900

Grid Grids[100][100];
Grid Edges[164];
Player player1(0.5, 0.5, 0.8, 0.4, 0);
vector<Zombie> zombies;

void findkill() {
	kill = 0;
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i].life == 0) {
			kill += 1;
		}
	}
}

//��ġ�� ���� grid�� return �ϴ� �Լ�
Grid searchGrid(float x1, float y1) {
	int i = (int)x1;
	int j = (int)y1;
	return Grids[i][j];

}
//��� ����Լ�
void lifeMinus(Player unknown) {
	//���� ���� �ʱ�ȭ
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			Grids[i][j].setTrace(0);
		}
	}
	player1.life -= 1;

	sp_key = 0;
}

//trace �ʱ�ȭ �Լ�
void initTrace() {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			Grids[i][j].setTrace(0);
		}
	}
}

//floodfill �ϱ� �� trace�� fil
void traceChange() {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (Grids[i][j].getTrace() == 1) {
				Grids[i][j].setState(1);
			}
		}
	}
}

//draw_string �Լ�
void draw_string(void*font, const char* str, float x, float y) {
	glRasterPos2f(x, y);
	for (int i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
}

//drawLine �Լ�
void drawLine(float x1, float y1, float x2, float y2) {
	glColor3f(1, 1, 1);
	glLineWidth(10.0f);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
//drawPoint �Լ�
void drawPoint(float x, float y) {
	glColor3f(0, 0, 1);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

//floodfill - �ܰ� ����ó����, �ѹ��⿡ ���� �� ����� �� ���� floodfill recursive
void floodfill(float x0, float y0, int dr) {
	if (x0 >= 1 && x0 <= 39 && y0 >= 1 && y0 <= 39) {
		if (Grids[(int)x0][(int)y0].getState() == 0) {
			Grids[(int)x0][(int)y0].setState(-1);
		}
		if (dr == 8) {
			if (Grids[(int)x0][(int)y0 + 1].getState() == 0 && y0 < 38) {
				floodfill(x0, y0 + 1, 8);
			}
			if (Grids[(int)x0 + 1][(int)y0].getState() == 0 && x0 < 38) {
				floodfill(x0 + 1, y0, 6);
			}
			if (Grids[(int)x0 - 1][(int)y0].getState() == 0 && x0 > 2) {
				floodfill(x0 - 1, y0, 4);
			}
			else {
				return;
			}
		}
		else if (dr == 6) {
			if (Grids[(int)x0 + 1][(int)y0].getState() == 0 && x0 < 38) {
				floodfill(x0 + 1, y0, 6);
			}
			if (Grids[(int)x0][(int)y0 + 1].getState() == 0 && y0 < 38) {
				floodfill(x0, y0 + 1, 8);
			}
			if (Grids[(int)x0][(int)y0 - 1].getState() == 0 && y0 > 2) {
				floodfill(x0, y0 - 1, 2);
			}
			else {
				return;
			}
		}
		else if (dr == 4) {
			if (Grids[(int)x0 - 1][(int)y0].getState() == 0 && x0 > 2) {
				floodfill(x0 - 1, y0, 4);
			}
			if (Grids[(int)x0][(int)y0 + 1].getState() == 0 && y0 < 38) {
				floodfill(x0, y0 + 1, 8);
			}
			if (Grids[(int)x0][(int)y0 - 1].getState() == 0 && y0 > 2) {
				floodfill(x0, y0 - 1, 2);
			}
			else {
				return;
			}
		}
		else if (dr == 2) {
			if (Grids[(int)x0][(int)y0 - 1].getState() == 0 && y0 > 2) {
				floodfill(x0, y0 - 1, 2);
			}
			if (Grids[(int)x0 + 1][(int)y0].getState() == 0 && x0 < 38) {
				floodfill(x0 + 1, y0, 6);
			}
			if (Grids[(int)x0 - 1][(int)y0].getState() == 0 && x0 > 2) {
				floodfill(x0 - 1, y0, 4);
			}
			else {
				return;
			}
		}
	}
	else {
		if (Grids[(int)x0][(int)y0].getState() == 1) {
			return;
		}
		else {
			Grids[(int)x0][(int)y0].setState(-1);
			if (dr == 8) {
				if ((int)y0 == 0) {
					if (Grids[(int)x0][(int)y0 + 1].getState() == 0) {
						floodfill(x0, y0 + 1, 8);
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}
			else if (dr == 6) {
				if ((int)x0 == 0) {
					if (Grids[(int)x0 + 1][(int)y0].getState() == 0) {
						floodfill(x0 + 1, y0, 6);
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}
			else if (dr == 4) {
				if ((int)x0 == 39) {
					if (Grids[(int)x0 - 1][(int)y0].getState() == 0) {
						floodfill(x0 - 1, y0, 4);
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}
			else if (dr == 2) {
				if ((int)y0 == 39) {
					if (Grids[(int)x0][(int)y0 - 1].getState() == 0) {
						floodfill(x0, y0 - 1, 2);
					}
					else {
						return;
					}
				}
				else {
					return;
				}
			}
		}
	}
}

//�Ųٷ� floodfill �Ѱ��� ����� �ٲ��ֱ�
void reverse() {
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			if (Grids[i][j].getState() == -1) {
				Grids[i][j].setState(0);
			}
			else if (Grids[i][j].getState() == 0) {
				Grids[i][j].setState(1);
			}
		}
	}
}

// flood fill ����
void fill() {
	for (int i = 1; i < 41; i++) {
		floodfill(Edges[i].getX(), Edges[i].getY() + 1, 8);
	}
	for (int i = 42; i < 82; i++) {
		floodfill(Edges[i].getX() + 1, Edges[i].getY(), 6);
	}
	for (int i = 82; i < 122; i++) {
		floodfill(Edges[i].getX() - 1, Edges[i].getY(), 4);
	}
	for (int i = 123; i < 163; i++) {
		floodfill(Edges[i].getX(), Edges[i].getY() - 1, 2);
	}
}

//gamestate �� 1�̸� ���� �����Լ�
//gamestate �� 2�̸� ������� �ٲ��ִ� �Լ�
void processSpecialKeys(int key, int x, int y) {
	if (game_state == 1) {
		if (!((key == GLUT_KEY_UP && level == 1) || (key == GLUT_KEY_DOWN && level == 4))) {
			switch (key) {
			case GLUT_KEY_DOWN:
				level += 1;
				break;
			case GLUT_KEY_UP:
				level -= 1;
				break;
			}
		}
	}

	else if (game_state == 2) {
		float x1 = player1.getX();
		float y1 = player1.getY();

		if (key == GLUT_KEY_RIGHT && x1 + 0.5 <= 40) {
			sp_key = 6;
		}
		else if (key == GLUT_KEY_LEFT && x1 - 0.5 >= 0) {
			sp_key = 4;
		}
		else if (key == GLUT_KEY_UP && y1 + 0.5 <= 40) {
			sp_key = 8;
		}
		else if (key == GLUT_KEY_DOWN && y1 - 0.5 >= 0) {
			sp_key = 2;
		}
	}
}

// grids, player1 �� �ʱ⼳��
void init() {
	/* Implement: Set each object */

	level = 1;
	sp_key = 0;
	zombienum = 0;
	territory = 0;
	player1.life = 3;

	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			Grids[i][j].setPos(i + 0.5, j + 0.5);
			Grids[i][j].setColor(0.2, 0.2, 0.2);
			Grids[i][j].setState(0);
		}
	}
	for (int i = 0; i < 42; i++) {
		Edges[i].setPos(i - 0.5, -0.5);
		Edges[i].setColor(1, 1, 1);
		Edges[i].setState(4);
	}
	for (int i = 42; i < 82; i++) {
		Edges[i].setPos(-0.5, i - 41.5);
		Edges[i].setColor(1, 1, 1);
		Edges[i].setState(4);
	}
	for (int i = 82; i < 122; i++) {
		Edges[i].setPos(40.5, i - 81.5);
		Edges[i].setColor(1, 1, 1);
		Edges[i].setState(4);
	}
	for (int i = 122; i < 164; i++) {
		Edges[i].setPos(i - 122.5, 40.5);
		Edges[i].setColor(1, 1, 1);
		Edges[i].setState(4);
	}
	player1.setPos(20.5, 20.5);
	zombies.clear();
	//�ʱ� player�� ����
	for (int i = (int)player1.getX() - 1; i <= (int)player1.getX() + 1; i++) {
		for (int j = (int)player1.getY() - 1; j <= (int)player1.getY() + 1; j++) {
			Grids[i][j].setState(1);
			Grids[i][j].setColor(0.6,0.6,0.2);
		}
	}
	initTrace();
}

//enter�� ������ game�� ���۵ǰ� �ϰ�, ���̵��� ���� zombie �ʱ⼳��
void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 'r') {
		game_state = 1;
		init();
		glutPostRedisplay();
	}

	if (game_state == 1 && key == 13) {
		game_state = 2;

		if (level == 1) {
			for (int i = 0; i < 3; i++) {
				zombies.push_back(Zombie());
				zombies[i].initset();
				zombies[i].setK(zombiespeed);
				zombienum++;
			}
		}

		else if (level == 2) {
			for (int i = 0; i < 6; i++) {
				zombies.push_back(Zombie());
				zombies[i].initset();
				zombies[i].setK(zombiespeed);
				zombienum++;
			}
		}

		else if (level == 3) {
			for (int i = 0; i < 18; i++) {
				zombies.push_back(Zombie());
				zombies[i].initset();
				zombies[i].setK(zombiespeed);
				zombienum++;
			}
		}

		else {
			for (int i = 0; i <30; i++) {
				zombies.push_back(Zombie());
				zombies[i].initset();
				zombies[i].setK(zombiespeed);
				zombienum++;
			}
		}
	}
}

//������¿� ���� player1�� ������ �ٲ��ִ� �Լ�
//zombies�� �������� zombieidle

void idle() {

		float x1 = player1.getX();
		float y1 = player1.getY();

		// Ű �ٲٸ� ���� �ٲ���. �ӵ� �����. (���� �ſ� ��ó �϶��� ���� �ٲ�)
		if (sp_key == 4) {
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (player1.getDirection() != 6) {
					player1.setDirection(4);
				}
			}
		}
		else if (sp_key == 6) {
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (player1.getDirection() != 4) {
					player1.setDirection(6);
				}
			}
		}
		else if (sp_key == 8) {
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (player1.getDirection() != 2) {
					player1.setDirection(8);
				}
			}
		}
		else if (sp_key == 2) {
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (player1.getDirection() != 8) {
					player1.setDirection(2);
				}
			}
		}
		else if (sp_key == 0) {
			player1.setDirection(0);
		}

		//direction ���� ������
		if (player1.getDirection() == 6) {
			if (x1 + 0.5 < 40) {
				player1.setPos(x1 + speed, y1);
			}
			if ((x1 - ((int)x1) >= 0.9-speed) && (x1 - ((int)x1) < 0.9+speed) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (Grids[((int)x1) + 1][(int)y1].getTrace() == 1) {
					lifeMinus(player1);
					player1.setPos(20.5, 20.5);
				}
			}
		}
		else if (player1.getDirection() == 4) {
			if (x1 - 0.5 > 0) {
				player1.setPos(x1 - speed, y1);
			}
			if ((x1 - ((int)x1) > 0.1- speed) && (x1 - ((int)x1) <= 0.1 + speed) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
				if (Grids[((int)x1) - 1][(int)y1].getTrace() == 1) {
					lifeMinus(player1);
					player1.setPos(20.5, 20.5);
				}
			}
		}
		else if (player1.getDirection() == 8) {
			if (y1 + 0.5 < 40) {
				player1.setPos(x1, y1 + speed);
			}
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= 0.9-speed) && (y1 - ((int)y1) < 0.9 + speed)) {
				if (Grids[((int)x1)][(int)y1 + 1].getTrace() == 1) {
					lifeMinus(player1);
					player1.setPos(20.5, 20.5);
				}
			}
		}
		else if (player1.getDirection() == 2) {
			if (y1 - 0.5 > 0) {
				player1.setPos(x1, y1 - speed);
			}
			if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <=test2) && (y1 - ((int)y1) > 0.1 - speed) && (y1 - ((int)y1) <= 0.1 + speed)) {
				if (Grids[((int)x1)][(int)y1 - 1].getTrace() == 1) {
					lifeMinus(player1);
					player1.setPos(20.5, 20.5);
				}
			}
		}

		//zombie�� ��ġ�� �ٲ��ִ� ��
		for (int i = 0; i < zombienum; i++) {
			int gridx = (int)zombies[i].getX();
			int gridy = (int)zombies[i].getY();

			zombies[i].randdir();
			//���� �� ���� grid state �� 1 �̸� �����Ե� �߰���.
			if (zombies[i].dir == 4) {
				zombies[i].setDirection(4);
				if (zombies[i].getX() - 0.5 > 0 && Grids[gridx - 1][gridy].getState() == 0) {
					zombies[i].setPos(zombies[i].getX() - 0.5 / zombies[i].k, zombies[i].getY());
				}
			}
			else if (zombies[i].dir == 6) {
				zombies[i].setDirection(6);
				if (zombies[i].getX() + 0.5 < 40 && Grids[gridx + 1][gridy].getState() == 0) {
					zombies[i].setPos(zombies[i].getX() + 0.5 / zombies[i].k, zombies[i].getY());
				}
			}
			else if (zombies[i].dir == 8) {
				zombies[i].setDirection(8);
				if (zombies[i].getY() + 0.5 < 40 && Grids[gridx][gridy + 1].getState() == 0) {
					zombies[i].setPos(zombies[i].getX(), zombies[i].getY() + 0.5 / zombies[i].k);
				}
			}
			else if (zombies[i].dir == 2) {
				zombies[i].setDirection(2);
				if (zombies[i].getY() - 0.5 > 0 && Grids[gridx][gridy - 1].getState() == 0) {
					zombies[i].setPos(zombies[i].getX(), zombies[i].getY() - 0.5 / zombies[i].k);
				}
			}

			if (searchGrid(zombies[i].getX(), zombies[i].getY()).getTrace() == 1) {
				lifeMinus(player1);
				player1.setPos(20.5, 20.5);
			}
			
			if (searchGrid(zombies[i].getX(), zombies[i].getY()).getState() == 1) {
				zombies[i].stop();
				zombies[i].life = 0;

			}

		}

		territory = 0;
		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 40; j++) {
				//trace �����ִ� �κ�
				if ((player1.getX() <= Grids[i][j].getX() + 0.5) && (player1.getX() >= Grids[i][j].getX() - 0.5)
					&& (player1.getY() <= Grids[i][j].getY() + 0.5) && (player1.getY() >= Grids[i][j].getY() - 0.5)) {
					if (Grids[i][j].getState() == 0) {
						if ((x1 - ((int)x1) >= test1) && (x1 - ((int)x1) <= test2) && (y1 - ((int)y1) >= test1) && (y1 - ((int)y1) <= test2)) {
							Grids[i][j].setTrace(1);
						}
					}
				}
				//���� ����(territory) update
				if (Grids[i][j].getState() == 1) {
					territory++;

				}
			}	
		}

		ratio = territory / 16;

		findkill();

		//���� �ܺο� ���� �����ϱ� ���� �Լ�
		if (searchGrid(player1.getX(), player1.getY()).getState() == 1) {
			if (firstpoint.size() == 0) {
				firstpoint.push_back(player1.getX());
				firstpoint.push_back(player1.getY());

			}
			else if (firstpoint.size() != 0 && secondpoint.size() != 0) {
				traceChange();
				fill();
				reverse();
				firstpoint.clear();
				secondpoint.clear();
				initTrace();
			}
		}

		else if (searchGrid(player1.getX(), player1.getY()).getState() == 0) {
			if (secondpoint.size() == 0) {
				secondpoint.push_back(player1.getX());
				secondpoint.push_back(player1.getY());
			}
		}

		// 60%�̻� �����߰ų�, life�� 0�̸� gamestate 3���� ��ȯ
		if (ratio >= 90 || player1.life <= 0) {
			game_state = 3;
		}
	
	glutPostRedisplay();
}

//ȭ�鿡 �׷��ִ� �Լ���
void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//kill �� string ���� �ٲ���
	ostringstream ost2;
	string st2;
	ost2 << kill;
	st2 = ost2.str();
	const char* ch2;
	ch2 = &st2[0];

	//�ʱ� �޴� ȭ��
	if (game_state == 1) {
		glColor3f(1, 1, 1);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "SELECT LEVEL", 16, 30);
		glColor3f(0, 1, 1);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "EASY", 19, 23);
		glColor3f(1, 1, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "NORMAL", 19, 21);
		glColor3f(1, 0, 1);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HARD", 19, 19);
		glColor3f(1, 0, 0);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "HELL", 19, 17);
		glColor3f(1, 1, 1);

		if (level == 1) {
			draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "->", 15, 23);
		}
		else if (level == 2) {
			draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "->", 15, 21);
		}
		else if (level == 3) {
			draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "->", 15, 19);
		}
		else if (level == 4) {
			draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "->", 15, 17);
		}
	}

	// ���� ���� ��Ȳ ȭ��
	else if (game_state == 2) {
		drawLine(-1, 42, 41, 42);
		drawLine(14, 46, 14, 42);
		drawLine(24, 46, 24, 42);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "LIFE", 0.2, 45.4);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "LEVEL", 14.4, 45.4);
		draw_string(GLUT_BITMAP_TIMES_ROMAN_10, "RATIO", 24.4, 45.4);
	
		for (int i = 0; i < player1.life; i++) {
			glColor3f(1, 0, 0);
			glPointSize(30.0f);
			glBegin(GL_POINTS);
			glVertex2f(1 + 4 * i, 44);
			glEnd();
		}

		if (level==1) {
			glColor3f(0, 1, 1);
			draw_string(GLUT_BITMAP_HELVETICA_18, "EASY", 17.5, 44);
		}
		else if (level == 2) {
			glColor3f(1, 1, 0);
			draw_string(GLUT_BITMAP_HELVETICA_18, "NORMAL", 17.5, 44);
		}
		else if (level == 3) {
			glColor3f(1, 0, 1);
			draw_string(GLUT_BITMAP_HELVETICA_18, "HARD", 17.5, 44);
		}
		else if (level == 4) {
			glColor3f(1, 0, 0);
			draw_string(GLUT_BITMAP_HELVETICA_18, "HELL", 17.5, 44);
		}

		//ratio ����
		//���� �� ����
		ostringstream ost;
		string st;
		ost << ratio;
		st = ost.str();
		const char* ch;
		ch = &st[0];
		glColor3f(1, 1, 0);
		draw_string(GLUT_BITMAP_HELVETICA_18, ch, 28, 44);
		draw_string(GLUT_BITMAP_HELVETICA_18, "%", 29, 44);
		glColor3f(0.3, 0.3, 0.3);
		draw_string(GLUT_BITMAP_HELVETICA_18, "(GOAL = 90%)", 30, 44);

		glColor3f(1, 1, 1);
		draw_string(GLUT_BITMAP_HELVETICA_12, "You've kiled", 15, 41.2);
		draw_string(GLUT_BITMAP_HELVETICA_12, ch2, 19, 41.2);
		draw_string(GLUT_BITMAP_HELVETICA_12, "enemy(enemies)!", 19.5, 41.2);

		for (int i = 0; i < 40; i++) {
			for (int j = 0; j < 40; j++) {
				Grids[i][j].draw();
			}
		}
		for (int i = 0; i < 164; i++) {
			Edges[i].draw();
		}

		player1.draw();

		for (int i = 0; i < zombienum; i++) {
			if (zombies[i].life == 1) {
				zombies[i].draw();
			}
		}
	}

	// ���� ���� ȭ��
	else if (game_state == 3) {
		if (player1.life <= 0) { //player life�� 0 -> Game Over 
			glColor3f(1, 1, 1);
			draw_string(GLUT_BITMAP_HELVETICA_12, "Game Over!", 15, 30);
			glColor3f(1, 1, 1);
			draw_string(GLUT_BITMAP_HELVETICA_12, "You've kiled", 15, 20);
			draw_string(GLUT_BITMAP_HELVETICA_12, ch2, 19, 20);
			draw_string(GLUT_BITMAP_HELVETICA_12, "enemy(enemies)!", 19.5, 20);
		}
		else { //player�� stage clear
			glColor3f(1, 1, 1);
			draw_string(GLUT_BITMAP_HELVETICA_12, "Game Clear!", 15, 30);
			glColor3f(1, 1, 1);
			draw_string(GLUT_BITMAP_HELVETICA_12, "You've kiled", 15, 20);
			draw_string(GLUT_BITMAP_HELVETICA_12, ch2, 19, 20);
			draw_string(GLUT_BITMAP_HELVETICA_12, "enemy(enemies)!", 19.5, 20);
		}
	}

	glutSwapBuffers();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(600, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Territory Expansion Game!");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 41, -1, 46);
	init();

	glutDisplayFunc(renderScene);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}