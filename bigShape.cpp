#include "bigShape.h"

/* the function check if the user want the shape to move right or left , if it possible, the shape is moving.
the function keep moving the shape down until the shape touch the floor of other shape and then send the
right points to update the borad*/
bool BigShape::move(Direction dir, Board &myMat)
{
	bool canMoveRightOrLeft = true;
	bool isTouchTheFloorOrSomething = false;
	int i;
	for (i = 0; i < SIZESHAPE; i++)
	{
		canMoveRightOrLeft = canMoveRightOrLeft && myMat.canMoveRightOrLeft(arrShape[i], dir);
	}

	if (canMoveRightOrLeft == false)
	{
		dir = CONTINUE;
	}
	// checking if one point of the line touching the floor or other shape
	for (i = 0; i < SIZESHAPE; i++)
	{
		isTouchTheFloorOrSomething = isTouchTheFloorOrSomething || (myMat.isOverTheFloorOrSomething(arrShape[i]));
	}

	if (isTouchTheFloorOrSomething == false)
	{//move the shape according the dir; move the point, delete the current shape and draw a new shape based on new point.
		draw(' ');
		for (auto& p : arrShape)
		{
			p.move(dir);
		}
		draw(c);
	}
	else
	{
		for (auto& p : arrShape)
		{
			myMat.updateMat(p);
		}
		return true;
	}

	return false;
}

/* the function works if the user press on SPACE and move the shape to the right points in the borad*/
void BigShape::immidiatlyDown(Board & myMat, int&distance) // space dir
{
	int i = SIZE_ROW -2 + PLUS_TO_XY_IN_SCREEN;
	int j;
	int currentY;
	currentY = findMaxPointInShapeAcordingTheY(arrShape).getY();
	int index = i - currentY;

	//checking in which row there is a place for the specipic shape and return the lowesr row. 
	for (i = SIZE_ROW  -2 + PLUS_TO_XY_IN_SCREEN; i > currentY; i--) // check where is the higher row that full in shapes
	{

		for (j = 0; j < SIZESHAPE; j++)
		{
			int distaceFromFloor = i - currentY ;
			if (myMat.checkIfFull({ arrShape[j].getX(), arrShape[j].getY() + distaceFromFloor }))
				index = distaceFromFloor-1;
		}

	}
	 // the place that we need to move the shape - up to the full row
	draw(' ');
	for (j = 0; j < SIZESHAPE; j++)
		arrShape[j].setY(arrShape[j].getY() + index);
	for (j = 0; j < SIZESHAPE; j++)
	{
		myMat.updateMat(arrShape[j]);
	}
	draw(c);
	distance = index;// update the hight from the shape to her new place for the score.
}
