#include "Ship.h"

using namespace std;

// Constructor
Ship::Ship()
	:Game_Actor(142,11,20,40,0)
{
	// Display the Ship ASCII code 18
	// color = 11 jade, high intensity
	// X=20 initial position column 20;
	// Y=40 ship always on line 40
	// 0 points when killed
	show();
}

/**
overloading copy constructor
*/
Ship::Ship(const Ship& p)
	:Game_Actor(18,15,15,40,0)
{
	//x=15 insted of 20
}

void Ship::move()
{
	// just because it is required by the father class, should not be used
	cout << "Error in Ship class, function move() called";
}

void Ship::move(char key_pressed)
{
	// ship can move between column 1 and 40
	switch (key_pressed)
	{
	case KEY_RIGHT:
		if (coord.X < 40) {
			moveTo(coord.X+1, coord.Y); // move right
		}
		break;
	case KEY_LEFT:
		if (coord.X > 1) {
			moveTo(coord.X - 1, coord.Y); // move left
		}
		break;
	}

}










