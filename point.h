#pragma once

#include <iostream>
#include "gotoxy.h"

using namespace std;
enum Direction { LEFT, RIGHT, ROTATE, DOWN,CONTINUE,SPACE_, S_JOKER};

class Point
{
	int x;
	int y;
	int dir_x;
	int dir_y;
	void moveImpl() {
		x = (x + dir_x);
		y = (y + dir_y);
	}
public:
	int getX() { return x; }
	int getY() { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }
	Point(int x1 = 4, int y1 =4) {
		x = x1;
		y = y1;
	}

	Point right() const {
		return Point(x + 1, y);
	}
	Point down() const {
		return Point(x, y + 1);
	}
	Point up() const {
		return Point(x, y - 1);
	}
	Point left() const {
		return Point(x-1, y );
	}
	void draw(char c = '*') const {
		gotoxy(x, y);
		cout << c;
		cout.flush();
	}
	void changeDir(Direction dir);
	void move(Direction dir) {
		changeDir(dir);
		moveImpl();
	}
};

