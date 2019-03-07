#pragma once

#include "point.h"
#include "shapes.h"

#define SIZE_ROW 16
#define SIZE_COL 11

class Shape;

class Board
{
public:
	enum eBoard {LIMIT ='|', FLOOR='-',EMPTY='e', FULL='f'};
private:
	char mat[SIZE_ROW][SIZE_COL];
public:
	Board();
	bool canMoveRightOrLeft(Point p, Direction dir);
	bool canJokerMoveRightOrLeft(Point p, Direction dir);
	bool isJokerOverTheFloor(Point p);
	bool isOverTheFloorOrSomething(Point p);
	void updateMat(Point p);
	char* ifFullLine();
	void deleteRows(Shape* myShape);
	void drawNewMat();
	bool checkIfFull( Point p);
	bool checkIfFloor( Point p);
	bool checkIfLimit( Point p);
	void makeEmpty(Point p);
};
