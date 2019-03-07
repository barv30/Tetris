#pragma once
#include "shapes.h"
#include "game.h"
class Bomb : public Shape
{

public:
	Bomb(Point& head, char ch) :Shape(head, head, head, head, ch) {};
	void blowingUp(Board & myMat, Point p);
	bool move(Direction dir, Board &myMat) override;
	void ifCanRotate(Board myMat)override {};
	void immidiatlyDown(Board &myMat,  int&distance)override;
};
