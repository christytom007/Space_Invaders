#pragma once
#include "Game_Actor.h"

/**
* the Ennemy_Fast move across the screen
* child of Game_Actor class
*/

class Enemy_Slow : public Game_Actor {
public:
	int speed;
	Enemy_Slow();
	void move();
private:
	bool LRdirection; // true= move toward the right, false = move toward the left
	bool FBdirection; //Forward Backword Direction
};

