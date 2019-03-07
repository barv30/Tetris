#pragma once
#include "shapes.h"
#include "game.h"
class BigShape : public Shape
{

public:
	BigShape(Point& head, Point& p2, Point& p3, Point& p4, char ch) :Shape(head, p2, p3, p4, ch) {};
	bool move(Direction dir, Board &myMat)override;
	void immidiatlyDown(Board & myMat, int&distance) override;

};
