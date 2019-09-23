#pragma once
#include "UIKit.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_ESC 27

#define COLOR_LIGHT_BLUE 1
#define COLOR_LIGHT_GREEN 2
#define COLOR_LIGHT_LBLUE 3
#define COLOR_LIGHT_RED 4
#define COLOR_LIGHT_PURPLE 5
#define COLOR_LIGHT_YELLOW 6
#define COLOR_LIGHT_WHITE 7

#define COLOR_BRIGHT_BLUE 9
#define COLOR_BRIGHT_GREEN 10
#define COLOR_BRIGHT_LBLUE 11
#define COLOR_BRIGHT_RED 12
#define COLOR_BRIGHT_PURPLE 13
#define COLOR_BRIGHT_YELLOW 14
#define COLOR_BRIGHT_WHITE 15

/**
* Father class for all game actors: ship, lasers, ennemies
* This is an abstract class, see move() function must be implemented in all child classes
*/
class Game_Actor
{
public:
	COORD coord;  // position on screen, see windows.h
	bool isAlive; // if alive it can move and can be killed for points

	// constructor see below for parameters
	Game_Actor(int Char_Code, int Color_Code, int x, int y, int Points);
	~Game_Actor(); // destructor

	// public methods
	void show() const;    // display the character
	int kill();
	virtual void move() = 0; // pure virtual->all child class must implement

protected:
	const int Char_Code;   // ASCII character to display
	const int Color_Code; // color of the character
	const int Points;     // nb of points when killed
	void moveTo(int x, int y); // move to a new position
	void hide() const;    // erase the character
};

