#pragma once
#include "game.h"

int Game::score = 0;

Shape* Game::randomAndCheckPlace(Board &myMat, int&type,bool& isTherePlace,Point head)
{
	bool checkIfLose;
	type = rand() %7; // WE HAVE SEVEN SHAPES
	Shape* my_Shape = currentShape( type,head);
	if (type != Shape::BOMB && type != Shape::JOKER)
	{
		checkIfLose = isLose(myMat, my_Shape);
		isTherePlace = (!checkIfLose);// there is no place in the board
	}
	else
		isTherePlace = true;
	return my_Shape;

}
Shape* Game::currentShape(int type, Point head)
{
	switch (type)
	{
	case(Shape::SQUARE):
	{
		setTextColor(CYAN);
		Shape* myShape = new BigShape( head, head.right(), head.down(), head.down().right(), '*');
		return myShape;
	}
	break;
	case(Shape::LINE):
	{
		setTextColor(LIGHTRED);
		Shape* myShape = new BigShape(head, head.right(), head.right().right(), head.right().right().right(), '*');
		return myShape;
	}
	break;
	case(Shape::ZED):
	{
		setTextColor(LIGHTCYAN);
		Shape*  myShape = new BigShape( head, head.right(), head.right().down(), head.right().down().right(), '*');
		return myShape;
	}
	break;
	case(Shape::SHIN):
	{
		setTextColor(MAGENTA);
		Shape*  myShape = new BigShape( head,head.right(), head.right().up(), head.right().right(), '*');
		return myShape;
	}
	break;
	case(Shape::EL):
	{
		setTextColor(RED);
		Shape*  myShape = new BigShape(head, head.down(), head.down().right(), head.down().right().right(), '*');
		return myShape;
	}
	break;
	case(Shape::JOKER):
	{
		setTextColor(YELLOW);
		Shape*  myShape = new Joker(head, '*');
		return myShape;
	}
	break;
	case(Shape::BOMB):
	{
		setTextColor(LIGHTBLUE);
		Shape*  myShape = new Bomb(head, '@');
			return myShape;
	}
	break;
	}

}

/*
this function print the board of the game and the menu
*/
void Game::printGame()
{
	gotoxy(0, 4);
	int i = 0;
	char ch = '|';
	for (i = 0; i < 15; i++)
	{
		setTextColor(WHITE);

		cout << ch;
		cout << "          ";
		cout << ch << endl;
	}
	cout << "^^^^^^^^^^^^" << endl;
	gotoxy(0, 1);
	setTextColor(LIGHTGREY);
	cout << "score:";
	gotoxy(15, 1);
	cout << "number of shapes:";
	gotoxy(20, 3);
	setTextColor(RED);
	cout << "** M   E   N    U **";
	gotoxy(20, 4);
	cout << "-------------------";
	setTextColor(LIGHTMAGENTA);
	gotoxy(20, 5);
	cout << "1. start game";
	gotoxy(20, 6);
	cout << "2. pause / resume game";
	gotoxy(20, 7);
	cout << "3. increase the rate of falling parts";
	gotoxy(20, 8);
	cout << "4. slow the rate of falling parts";
	gotoxy(20, 9);
	cout << "5. return to normal rate";
	gotoxy(20, 10);
	cout << "6. exit game";

	setTextColor(RED);
	gotoxy(20, 12);
	cout << "**KEY GAME:**";
	gotoxy(20, 13);
	cout << "-------------";
	gotoxy(20, 14);
	setTextColor(LIGHTMAGENTA);
	cout << "'g' - left , 'h'-right , 'b'- fast down";
	gotoxy(20, 15);
	cout << "'y'-rotate, 's'- stop the joker ,SPACE- immidiatly down";
}

// this function run all the other function. the game is running while the paramer userWantsToPlay==true.
// this paramer turns to false when the user ask to exit the game or the user lose.
void Game::firstRun()
{
	bool isStartNewGame = false;
	bool userWantsToPlay = true;
	char menuSelection;
	Board myMat;
	while (userWantsToPlay)
	{
		if (isStartNewGame == true) // the user want to start new game
		{
			Board newMat;
			printGame();
			score = 0;
			Shape::counterShapes = 0;
			isStartNewGame = false;
			gotoxy(0, 20);
			cout << "its a new game                             ";
			startGame(isStartNewGame, userWantsToPlay, newMat);
		}
	 //checking for the user to press 1 to start the game
		if (_kbhit())
		{
			menuSelection = _getch();

			if (menuSelection == '1') //start new game
			{
				gotoxy(5, 2);
				cout << "                                              ";
					startGame(isStartNewGame, userWantsToPlay, myMat);
			}
		
			else  // if the user press any other key , he get a messege that he has to press 1
			{
				gotoxy(5, 2);
				cout << "you should press 1 in order to start the game";
			}
		}
	}
}

/* function that works when the user start the game. stop working when the user want to stop or 
when the user loose*/
void Game::startGame(bool& isStartNewGame, bool &userWantsToPlay, Board & myMat)
{
	int sleeping = NORMAL;
	while (alwaysRun(myMat, sleeping, isStartNewGame))// כל עוד לא נפסל
	{
		///
	}
	gotoxy(0, 20);
	
	if (isStartNewGame==false) 
	{
		userWantsToPlay = false;
	cout << " -------- G A M E   O V E R --------" << endl;
	}
	return;
}
/* this function check if the user don't loose. make new shapes until the user loose.
the function also check which key the user press and sent to the right function that we need to move*/
bool Game::alwaysRun(Board &myMat, int& sleeping, bool& isStartNewGame)
{
	int addToScore;
	int type;
	Direction dir;
	bool isTherePlace;
	bool isFinishThisShape = false;
	Shape* my_shape;
	my_shape = randomAndCheckPlace(myMat, type, isTherePlace, head);
	if (isTherePlace == true)
	{
		while (true)
		{
			char keyPressed = 0;
			if (_kbhit())
			{
				keyPressed = _getch();
				switch (keyPressed)
				{
				case('1'):
				{
					isStartNewGame = true;
					return false;
				}
				case ('2'):
				{
					gotoxy(0, 20);
						system("Pause");
						gotoxy(0, 20);
						cout << "                                           ";
	
				}
				break;
				case('3'):
				{
					sleeping = FAST;
				}
				break;
				case('4'):
				{
					sleeping = SLOW;
				}
				break;
				case('5'):
				{
					sleeping = NORMAL;
				}
				break;
				case('6'):
				{
					return false;
				}
				break;
				case(KEYS::ESC):
				{
					return false;
				}
				break;
				case(KEYS::SPACE):
				{
					// inside if
				}
				break;
				case (KEYS::SJOKER):
				{
				if (typeid(*my_shape)==(typeid(Joker)) )
					{
						dir = (Direction)S_JOKER;
						isFinishThisShape = my_shape->move(dir, myMat);
					}
					else
						keyPressed = 0;

				}
				break;

				default:
				{
					if (keyPressed != 'g' && keyPressed != 'h' && keyPressed != 'y'&& keyPressed != 'b' && keyPressed!= ' ')
						keyPressed = 0;
				}

				}
			}
			dir = my_shape->getDir(keyPressed);

		

			if (dir == ROTATE && type != Shape:: SQUARE)
			{
					my_shape->ifCanRotate(myMat);
			}
			if (dir == (Direction)SPACE_)
			{
				my_shape->immidiatlyDown(myMat, addToScore);
				score += addToScore * 2;
				isFinishThisShape = true;
			
			}

			if (dir == DOWN || keyPressed != 0)
			{
				if (dir == DOWN)
				{
					score++;
				}
				Sleep(50);
			}
			else
				Sleep(sleeping);


			if (dir != SPACE_ && dir != ROTATE && dir != S_JOKER)
			{
				isFinishThisShape = my_shape->move(dir, myMat);
			}

			if (isFinishThisShape == true)
			{
				myMat.deleteRows(my_shape);
				delete my_shape;
				break;
			}

			gotoxy(7, 1);
			cout << "      ";
			gotoxy(7, 1);
			cout << score;
			gotoxy(34, 1);
			cout << "      ";
			gotoxy(34, 1);
			cout << Shape::counterShapes;

		}
		return true; // countinue game
	}
	return false;//finish game
}

/*
this function checking if the user lose the game
if its a bomb or joker the uder cant lose, the only way to lose is if it line or squere.
it checking if the last row in full in the specific places the shapes full down to the game.
*/
bool Game::isLose(Board &myMat, Shape* myShape)
{
		for (int i = 0; i < SIZESHAPE; i++)
		{
			if (myMat.checkIfFull(myShape->arrShape[i]) == true)
				return true;
		}
	return false;
}