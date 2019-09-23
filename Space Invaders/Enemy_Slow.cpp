#include "Enemy_Slow.h"

// constructor ------------------------------------------------
Enemy_Slow::Enemy_Slow()
	: Game_Actor(234, 5, 0, 0, 100) {
	// Display ASCII character code 234, color code 5
	// 100 points when killed
	coord.X = rand() % 40 + 1; // randomly set the initial position
	coord.Y = rand() % 20 + 1;
	LRdirection = true;
	FBdirection = true;
	show();
	speed = 0;
}

// move function ----------------------------------------------
void Enemy_Slow::move() {
	speed++;
	if (speed % 4 == 0) {
		if (LRdirection) {
			// move toward the right
			moveTo(coord.X + 1, coord.Y); // move right
			if (coord.X == 40) {
				// change direction
				LRdirection = false;
			}
		}
		else {
			// move toward the left
			moveTo(coord.X - 1, coord.Y); // left
			if (coord.X == 1) {
				// change direction
				LRdirection = true;
			}
		}
		
		if (FBdirection) {
			// move toward the forward
			moveTo(coord.X, coord.Y + 1); // move forward
			if (coord.Y == 20) {
				// change direction
				FBdirection = false;
			}
		}
		else {
			// move toward the backward
			moveTo(coord.X , coord.Y - 1); // backward
			if (coord.Y == 1) {
				// change direction
				FBdirection = true;
			}
		}
	}
	if (speed > 999999) {
		speed = 0;
	}
}