#include "point.h"

/*
this function return two paramters that are addion to the current x,y of the shape,
in order to move the shape's points in the pressed direction
*/

void Point::changeDir(Direction dir) {
	switch (dir) {
	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	case Direction::ROTATE:
	{
		//
	}
		break;
	case Direction::CONTINUE:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}