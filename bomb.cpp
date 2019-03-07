#include "bomb.h"

/* the function "blow up* all the shapes in distance 3X3 from the bomb */
void Bomb::blowingUp(Board & myMat, Point p)
{
	int i, j;
	int currentY = p.getY();
	int currentX = p.getX();
	Point tempP;
	p.draw(' ');
	for (i = currentX - 1; i <= currentX + 1 && i < SIZE_COL; i++)
	{
		for (j = currentY - 1; j <= currentY + 1 && j < SIZE_ROW + PLUS_TO_XY_IN_SCREEN - 1; j++)
		{
			if (i > 0 && j >= 0)// if it in the limit of the board
			{
				tempP.setX(i);
				tempP.setY(j);
				if (myMat.checkIfFull(tempP) == true)// check for the score if the bomb overribe a tail
				{
					tempP.draw(' ');
					myMat.makeEmpty(tempP);
					Game::score -= 50;
				}

			}
		}
	}
}

/* the function check if the user want the shape to move right or left , if it possible, the shape is moving.
the function keep moving the shape down until the shape touch the floor of other shape and then send the
right points to update the borad*/
bool Bomb::move(Direction dir, Board & myMat)
{

	bool canMoveRightOrLeft = true;
	bool isTouchTheFloorOrSomething = false;

	if (dir == RIGHT || dir == LEFT)
	{
		canMoveRightOrLeft = myMat.canMoveRightOrLeft(arrShape[0], dir);

	}
	if (canMoveRightOrLeft == false)
	{
		dir = CONTINUE;
	}
	isTouchTheFloorOrSomething = myMat.isOverTheFloorOrSomething(arrShape[0]);
	if (isTouchTheFloorOrSomething == false)
	{ //move the shape according the dir; move the point, delete the current shape and draw a new shape based on new point.
		for (const auto& p : arrShape)
		{
			p.draw(' ');
		}
		for (auto& p : arrShape)
		{
			p.move(dir);
		}
		for (const auto& p : arrShape)
		{
			p.draw(c);
		}
	}
	else//blowing up 
	{
		blowingUp(myMat, arrShape[0]);
		return true;
	}
	return false;
}

/* the function works if the user press on SPACE and move the shape to the right points in the borad*/
void Bomb::immidiatlyDown(Board &myMat, int&distance)
{
	int i = SIZE_ROW - 2 + PLUS_TO_XY_IN_SCREEN;
	int index = SIZE_ROW - 1 + PLUS_TO_XY_IN_SCREEN;
	int currentY, currentX;
	currentY = arrShape[0].getY();
	currentX = arrShape[0].getX();

	for (i = SIZE_ROW - 2 + PLUS_TO_XY_IN_SCREEN; i > currentY; i--) // check where is the higher row that full in shapes
	{
		if (myMat.checkIfFull({ currentX, i }) == true)
			index = i;
	}

	index = index - 1;
	//palcing the bomb and than caleed the func that blowing up all the shapes in 3x3 area of the bomb.
	myMat.updateMat({ currentX, index });
	for (const auto& p : arrShape)
	{
		p.draw(' ');
	}
	for ( auto& p : arrShape)
	{
		p.setY(index);
	}
	
	for (const auto& p : arrShape)
	{
		p.draw(c);
	}
	Sleep(50);
	blowingUp(myMat, arrShape[0]);

	distance = index;
}