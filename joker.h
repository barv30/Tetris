#pragma once
#include "shapes.h"
#include "game.h"
class Joker : public Shape
{

public:
	Joker(Point& head, char ch) :Shape(head, head, head, head, ch) {};
	bool move(Direction dir,  Board &myMat) override;
	void ifCanRotate(Board myMat)override {};
	void immidiatlyDown(Board &myMat, int&distance)override;

};
