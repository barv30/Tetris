#pragma once
#include <iostream>
using namespace std;

#include <stdio.h> 
#include <Windows.h>
#include <conio.h>
#include "gotoxy.h"
#include "point.h"
#include "shapes.h"
#include "board.h"
#include "Color.h"
#include "io_utils.h"
#include "bigShape.h"
#include <typeinfo>
#include "joker.h"
#include "bomb.h"

enum eSleep{FAST = 100, NORMAL = 250, SLOW = 500};
enum KEYS { ESC = 27, SPACE=32 ,SJOKER=115};
#define PLUS_TO_XY_IN_SCREEN 4
class Game
{
	Point head = { PLUS_TO_XY_IN_SCREEN +  0 ,4 };
	char ch;
	Shape::ShapeType whichShape;
public:
	static int score;
	Shape* randomAndCheckPlace(Board &myMat, int&type, bool& isTherePlace, Point p);
	Shape* currentShape( int type,Point p);
	void printGame();
	void firstRun();
	void startGame(bool& isPause, bool &userWantsToPlay, Board& myMat);
	bool alwaysRun(Board &myMat, int& sleeping, bool& isPause);
	bool isLose(Board &myMat, Shape* myShape);
	Game() {
		score = 0;
		printGame();
	}
};