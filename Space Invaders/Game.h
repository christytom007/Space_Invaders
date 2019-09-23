#pragma once
#pragma comment(lib, "winmm.lib") //for sound 

#include "Ship.h"
#include "Laser_Ship.h"
#include "Enemy_Fast.h"
#include "Enemy_Slow.h"
#include "Laser_Enemies.h"

#include <Windows.h> //for sound
#include <mmsystem.h> //for sound

#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

class Game
{
public:
	int Play(); // return: 0=>Game Over, 1=>You win, 2=>You Quit
	int getScore();
	int getLevel();
	Game(); //constructor
	~Game(); //destructor

private:
	int score;
	int level; // use if doing multiple levels
	bool Game_Paused;

	// game color
	const int Game_Info_Color = 15; // white

	// the Ship
	Ship My_Ship;

	// ship lasers array
	const int Max_Nb_Ship_Lasers = 50;
	Laser_Ship *Ship_Lasers[50]; // array of pointers
	int Nb_ShipLasers; // current number in array

	// enemy lasers array
	const int Max_Nb_Enemy_Lasers = 20;
	Laser_Enemies *Enemy_Lasers[20]; // array of pointers
	int Nb_EnemyLasers; // current number in array

	// ET Enemy_Fast array
	Enemy_Fast *ET_List[15];// array of pointers
	int Nb_ETs; // current number in array
	int ET_Period;// create a new one every ET_Period seconds
	clock_t last_ET_time; // time when the last ennemy was created
	clock_t last_Laser_time; // time when the last ennemy laser was created
	int Laser_Period;// create new Lasers every Laser_Period seconds

	//ET Enemy_Slow array
	bool EnableSlowEnemy; //enables the creation of slow enemy
	Enemy_Slow* ET_List_Slow[5]; //Array of slow Enemys
	int Nb_ETs_Slow; //number of slow enemy created

	int GameSpeed; //game speed value

	// ### TODO these functions implementation in Game.cpp
	void Ship_Laser_Create(); //create our ship lasers
	void Ship_Lasers_Move_All(); // move our ship lasers

	bool Check_Ship_Killed(); //check our ship is killed
	
	void ETs_Move_All(); //Move ETs
	void Check_ETs_Killed(); //check each enemy killed
	void Enemies_Create(); //create a new enemy Periodically
	int Enemies_Get_Total_Alive(); //return the number of enemy alive
	bool Enemies_Check_All_Killed(); //checking if all the enemy killed
	
	void Enemy_Lasers_Move_All(); // move all the enemy
	void Create_Enemy_Laser(int x, int y); //create enemy laser for one enemy

	void Level_Conditions(); //check the level conditions and difficulty changes
	void Create_Enemy_Lasers_Periodically(); //to create enemy lasers Periodically
	void initGame(); //initialize the game
};

