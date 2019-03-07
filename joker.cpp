#include "joker.h"

/* the function check if the user want the shape to move right or left , if it possible, the shape is moving.
the function keep moving the shape down until the shape touch the floor of other shape and then send the
right points to update the borad*/
bool Joker::move(Direction dir, Board & myMat) 
{
	bool canMoveRightOrLeft = true;
	bool isTouchTheFloorOrSomething = false;

	if (dir == S_JOKER) // placing the joker in the current place it is.
	{
		myMat.updateMat(arrShape[0]);
		return true;
	}
	else
	{
		if (dir == RIGHT || dir == LEFT)
		{
			canMoveRightOrLeft = myMat.canJokerMoveRightOrLeft(arrShape[0], dir);

		}
		if (canMoveRightOrLeft == false)
		{
			dir = CONTINUE;
		}

		isTouchTheFloorOrSomething = myMat.isJokerOverTheFloor(arrShape[0]);
		if (isTouchTheFloorOrSomething == false)
		{ //check if the joker need to be drawn or not for not override other shapes, according the diffrent direction that pressed.
			if (dir == CONTINUE)
			{
				if (myMat.checkIfFull(arrShape[0].down()) == true)
				{

					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
				}
				else
				{
					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
					draw(c);
				}
			}
			else if (dir == RIGHT)
			{
				if (myMat.checkIfFull(arrShape[0].right()) == true)
				{
					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
				}
				else
				{
					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
					draw(c);
				}
			}
			else if (dir == LEFT)
			{
				if (myMat.checkIfFull(arrShape[0].left()) == true)
				{
					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
				}
				else
				{
					if (myMat.checkIfFull(arrShape[0]) == false)
					{
						draw(' ');
					}
					for (auto& p : arrShape)
					{
						p.move(dir);
					}
						draw(c);
				}
			}

		}
		else
		{
			myMat.updateMat(arrShape[0]);
			return true;
		}
	}
	return false;
}

/* the function works if the user press on SPACE and move the shape to the right points in the borad*/
void Joker::immidiatlyDown(Board &myMat,  int&distance)
{
	int i = SIZE_ROW - 2 + PLUS_TO_XY_IN_SCREEN;
	int currentY, currentX;
	currentY = arrShape[0].getY();
	currentX = arrShape[0].getX();

	if (myMat.checkIfFull({ currentX, i }) == false)
	{
		myMat.updateMat({ currentX, i });
		draw(' ');
		for ( auto& p : arrShape)
		{
			p.setY(i);
		}
			draw(c);
	}
	else
	{
		if (myMat.checkIfFull({ currentX, currentY }) == false)
		{
			draw(' ');
		}
	}
	distance = i - currentY;
}