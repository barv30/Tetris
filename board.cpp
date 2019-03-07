#include "board.h"
#include "game.h"

// make new game borad. enter char to the right position- empty, floor or limit
Board::Board()
{
	int i, j;
	for (i = 0; i < SIZE_ROW; i++)
	{
		mat[i][0] = LIMIT;
		mat[i][SIZE_COL-1] = LIMIT;
	}
	for (i = 0; i < SIZE_COL;i++)
	{
		mat[SIZE_ROW-1][i] = FLOOR;
	}
	for (i = 0; i < SIZE_ROW-1; i++)
	{
		for (j = 1; j < SIZE_COL; j++)
		{
			mat[i][j] = EMPTY;
		}
	}
}

/*this function accepet point and direction and check if the user can move the shape
right or left. if there a "full" char or "limit" char in the board-
the user can't move the shape*/
bool Board::canMoveRightOrLeft(Point p, Direction dir)
{
	if (dir == RIGHT)
	{
		if (mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX() + 1] != LIMIT && mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX() + 1] != FULL)
			return true;
		return false; 
	}
	else if (dir == LEFT)
	{
		if (mat[p.getY()- PLUS_TO_XY_IN_SCREEN][p.getX()-1] != LIMIT && mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX() - 1] != FULL)
			return true;
		return false;
	}

	return false;
}

/*this function accepet point and direction and check if the user can move the shape
right or left. if there a "limit" char in the board-
the user can't move the shape
the function don't check if there a "full" char because the joker can move on shapes*/

bool Board::canJokerMoveRightOrLeft(Point p, Direction dir) // if joker can move
{
	if (dir == RIGHT)
	{
		if (mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX() + 1] != LIMIT)
			return true;
		return false;
	}
	else if (dir == LEFT)
	{
		if (mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX() - 1] != LIMIT )
			return true;
		return false;
	}

	return false;
}
/* this function accept a point and check if the joker touch the floor at the next move.*/
bool Board::isJokerOverTheFloor(Point p)
{
	if (mat[(p.getY() - PLUS_TO_XY_IN_SCREEN) + 1][p.getX()] == FLOOR)
		return true;
	return false;
}

/* this function accept a point and check if the shape(if not joker) touch the floor at the next move.*/
bool Board::isOverTheFloorOrSomething(Point p)
{

	if (mat[(p.getY() - PLUS_TO_XY_IN_SCREEN) + 1][p.getX()] == FLOOR || mat[(p.getY() - PLUS_TO_XY_IN_SCREEN) + 1][p.getX()] == FULL)
	{
		return true;
	}
	return false;
}

// insert "full" char in the board
void Board::updateMat( Point p)
{
	mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX()] = FULL;

}

// check if there is full line in the board- full with shapes
char* Board:: ifFullLine()
{
	int i, j;
	int counter = 0;
	char *arrIndex;
	arrIndex = new char[SIZE_ROW-1];
	for (i = 0; i < SIZE_ROW-1; i++)
	{
		for (j = 1; j < SIZE_COL;j++) {
			if (mat[i][j] == FULL)
				counter++;
		}
		if (counter == SIZE_COL-1)
		{
			arrIndex[i] = '1';
		}
		else
		{ 
			arrIndex[i] = '0';
		}
		counter = 0;
	}
	return arrIndex
	;
}

/* this function delete full row from the board and update the mat*/
void Board::deleteRows(Shape* myShape)
{
	char *arr = ifFullLine();
	int counterDeletedRows = 0;
	int i, j, k, l;
	for (i = 0; i < SIZE_ROW - 1; i++)
	{
		if (arr[i] == '1')
		{
			counterDeletedRows++;
			for (k = 1; k < SIZE_COL; k++)
			{
				mat[i][k] = EMPTY;
			}
			for (j = i - 1; j >= 0; j--)
			{
				for (l = 1; l < SIZE_COL; l++)
				{
					if (mat[j][l] == FULL)
					{
						mat[j][l] = EMPTY;
						mat[j + 1][l] = FULL;
					}
				}
				setTextColor(BROWN);
				drawNewMat();
			}
			
		}
	}

	if (typeid(myShape) == typeid(Joker) && counterDeletedRows > 0)
		Game::score += 50;
	else if (counterDeletedRows == 1)
		Game::score += 100;
	else if(counterDeletedRows == 2)
		Game::score += 300;
	else if(counterDeletedRows == 3)
		Game::score += 500;

	delete[]arr;
}

/* this function draw new borad after delete rows*/
void Board::drawNewMat()
{
	int i, j;
	for (i = 0; i < SIZE_ROW-1; i++)
	{
		for (j = 1; j < SIZE_COL; j++)
		{
			if (this->mat[i][j] == FULL) {
				gotoxy(j, i + PLUS_TO_XY_IN_SCREEN);
				cout << "*";
			}
			else
			{
				gotoxy(j, i + PLUS_TO_XY_IN_SCREEN);
				cout << " ";
			}
		}
	}
}

/* this function check if the borad have char "full" at the point*/
bool Board::checkIfFull(Point p)
{
	if ((mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX()] == FULL) )
		return true;
	return false;
}

/* this function check if the borad have char "floor" at the point*/
bool Board::checkIfFloor(Point p)
{
	if ((mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX()] == FLOOR))
		return true;
	return false;
}

/* this function check if the borad have char "limit" at the point*/
bool Board::checkIfLimit( Point p)
{
	if ((mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX()] == LIMIT))
		return true;
	return false;
}

//insetr char "empty" to the point at the board
void Board::makeEmpty( Point p)
{
	mat[p.getY() - PLUS_TO_XY_IN_SCREEN][p.getX()] = EMPTY;
}