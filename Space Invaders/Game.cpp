#include "Game.h"
#include <conio.h>
#include <fstream>
#include<string>


//### TODO FUNCTIONS ***************************************
//-----------------------------------------------------
/**
Create Ship laser
*/
void Game::Ship_Laser_Create() {
	//### TODO
	int x = My_Ship.coord.X; //get coordinate of Ship
	int y = My_Ship.coord.Y - 1;

	for (int i = 0; i < Nb_ShipLasers; i++) {
		if (Ship_Lasers[i]->isAlive == false) { //check if any unused ship lasers
			PlaySound(TEXT("sound/ship_Laser.wav"), NULL, SND_FILENAME | SND_ASYNC);
			Ship_Lasers[i]->restart(x, y); //if found restart the ship laser with new coordinates
			return;
		}
	}
	if (Nb_ShipLasers < Max_Nb_Ship_Lasers) { // if total ship lasers created are less than maximum number of ship lasers
		PlaySound(TEXT("sound/ship_Laser.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Ship_Lasers[Nb_ShipLasers] = new Laser_Ship(x, y); //create a new ship laser
		Nb_ShipLasers++; //increase ship laser count
	}
}

//-----------------------------------------------------
/**
Move all the enemy ship lasers
*/
void Game::Enemy_Lasers_Move_All() {
	//### TODO
	for (int i = 0; i < Nb_EnemyLasers; i++) { //for all the enemy lasers created move the lasers
		if (Enemy_Lasers[i]->isAlive) //check if the lasers is currently on the screen, only then move
			Enemy_Lasers[i]->move(); 
	}
}

//-----------------------------------------------------
/**
Checking if player ship is killed
*/
bool Game::Check_Ship_Killed() {
	//### TODO
	for (int i = 0; i < Nb_EnemyLasers; i++) { //cycle through all the enemy lasers created
		if (Enemy_Lasers[i]->coord.X == My_Ship.coord.X && Enemy_Lasers[i]->coord.Y == My_Ship.coord.Y && Enemy_Lasers[i]->isAlive) 
			//compare the enemy laser coordinate and player ship coordinate, also check if enemy laser is currenly in use
			return true; //if the conditions are meat, retun true
	}
	return false;
}

//-------------------------------------------------------
/**
Move all the player ship lasers
*/
void Game::Ship_Lasers_Move_All() {
	//### TODO
	for (int i = 0; i < Nb_ShipLasers; i++) { //for all the ship lasers created and that is on the screen, move them
		if (Ship_Lasers[i]->isAlive)
			Ship_Lasers[i]->move();
	}
}

//-------------------------------------------------------
/**
Periodically create enemy lasers
*/
void Game::Create_Enemy_Lasers_Periodically() {
	clock_t t;

	t = clock() - last_Laser_time; //get the difference duration between last enemy laser created
	if ((((float)t) / CLOCKS_PER_SEC) > Laser_Period) { //if the duration in greater than the Laser_Period
		last_Laser_time = clock(); //put the current time in last_Laser_time

		PlaySound(TEXT("sound/enemy_Laser.wav"), NULL, SND_FILENAME | SND_ASYNC);

		for (int i = 0; i < Nb_ETs; i++) {// for each Fast enemy that is alive in the screen
			if (ET_List[i]->isAlive)
				Create_Enemy_Laser(ET_List[i]->coord.X, ET_List[i]->coord.Y + 1); //create enemy laser for that enemy
		}
		for (int i = 0; i < Nb_ETs_Slow; i++) {// for each Slow enemy that is alive in the screen
			if (ET_List_Slow[i]->isAlive)
				Create_Enemy_Laser(ET_List_Slow[i]->coord.X, ET_List_Slow[i]->coord.Y + 1); //create enemy laser for that enemy
		}
	}
}

//-------------------------------------------------------
/**
Create new enemy laser based on the coordinate that is given in x,y
*/
void Game::Create_Enemy_Laser(int x, int y) {
	//### TODO
	for (int i = 0; i < Nb_EnemyLasers; i++) { //first check if any enemy lasers that is unused
		if (Enemy_Lasers[i]->isAlive == false) {
			Enemy_Lasers[i]->restart(x, y); //restart if any enemy lasers that is unused
			return;
		}
	}
	Enemy_Lasers[Nb_EnemyLasers] = new Laser_Enemies(x, y); //if no enemy lasers are found unsed create a new one
	Nb_EnemyLasers++; //increase the enemy laser count
}

//-------------------------------------------------------
/**
move all the enemyis that is alive
*/
void Game::ETs_Move_All() {
	//### TODO
	for (int i = 0; i < Nb_ETs; i++) { //check all the Fast enemy that is alive and move
		if (ET_List[i]->isAlive) {
			ET_List[i]->move();
		}
	}
	for (int i = 0; i < Nb_ETs_Slow; i++) { //check all the Slow enemy that is alive and move
		if (ET_List_Slow[i]->isAlive) {
			ET_List_Slow[i]->move();
		}
	}
}

//-------------------------------------------------------
/**
check if an enemy is killed
*/
void Game::Check_ETs_Killed() {
	//### TODO	
	for (int i = 0; i < Nb_ETs; i++) //cycle through all the Fast enemies
		for (int j = 0; j < Nb_ShipLasers; j++) { //cycle through all the ship lasers
			if ((ET_List[i]->isAlive) && (ET_List[i]->coord.X == Ship_Lasers[j]->coord.X) && (ET_List[i]->coord.Y == Ship_Lasers[j]->coord.Y) && (Ship_Lasers[j]->isAlive)) {
				//if the player ship laser coordinate and enemy coordinate are same and both are in screen the kill the enemy and add the point of the enemy into the score 
				score += ET_List[i]->kill();
			}
		}

	for (int i = 0; i < Nb_ETs_Slow; i++) //cycle through all the Slow enemies
		for (int j = 0; j < Nb_ShipLasers; j++) { //cycle through all the ship lasers
			if ((ET_List_Slow[i]->isAlive) && (ET_List_Slow[i]->coord.X == Ship_Lasers[j]->coord.X) && (ET_List_Slow[i]->coord.Y == Ship_Lasers[j]->coord.Y) && (Ship_Lasers[j]->isAlive)) {
				//if the player ship laser coordinate and enemy coordinate are same and both are in screen the kill the enemy and add the point of the enemy into the score 
				score += ET_List_Slow[i]->kill();
			}
		}

}

//-------------------------------------------------------
/**
create enemy periodically
*/
void Game::Enemies_Create() {
	clock_t t;
	int randomNumber = 20; //default randon number is set to less than 25

	t = clock() - last_ET_time; //get the last time enemy created
	if ((((float)t) / CLOCKS_PER_SEC) > ET_Period) { //if the last enemy created is greater than the ET_Period
		last_ET_time = clock();
		//### TODO

		if (EnableSlowEnemy) //if the Slow enemy is enabled generate a random number
			randomNumber = rand() % 50 + 1;

		if (randomNumber <= 25) { //by default the Fast enemy will be crated if Slow enemy is disabled
			for (int i = 0; i < Nb_ETs; i++) {
				if (ET_List[i]->isAlive == false) { //check if any unused enemy, if there is one revive it
					ET_List[i]->isAlive = true;
					return;
				}
			}
			ET_List[Nb_ETs] = new Enemy_Fast; //if ther is no unused enemy in the array create a new one
			Nb_ETs++; //increase the Fast enemy count
		}
		else { //if the Slow enemy is enabled and random number is greater than 25
			for (int i = 0; i < Nb_ETs_Slow; i++) { //check if any Slow enemy is unused, revive it
				if (ET_List_Slow[i]->isAlive == false) {
					ET_List_Slow[i]->isAlive = true;
					return;
				}
			}
			ET_List_Slow[Nb_ETs_Slow] = new Enemy_Slow; //if no unused enemy in the array create a new Slow enemy
			Nb_ETs_Slow++; //increase the Slow enemy count
		}
	}
}

//-------------------------------------------------------
/**
Return the total number of enemies alive
*/
int Game::Enemies_Get_Total_Alive() {
	//### TODO
	int temp = 0;
	for (int i = 0; i < Nb_ETs; i++) {
		if (ET_List[i]->isAlive == true) //count all the Fast enemy that is alive
			temp++;
	}
	for (int i = 0; i < Nb_ETs_Slow; i++) { //count all the Slow enemy that is alive
		if (ET_List_Slow[i]->isAlive == true)
			temp++;
	}
	return(temp);// return the count
}

//-------------------------------------------------------
/**
check if there is any enemy available
*/
bool Game::Enemies_Check_All_Killed() {
	//### TODO

	if (Enemies_Get_Total_Alive() == 0) {
		return true;
	}
	else {
		return false;
	}
}

//--------------------------------------------------------------
/**
Change difficulty based on score and level
*/
void Game::Level_Conditions() {

	//score criteria for increasing level
	if (score > 200 && level == 1)
		level++;

	if (score > 400 && level == 2)
		level++;

	if (score > 600 && level == 3)
		level++;


	//change dificulty based on the level
	if (level == 2) {
		Laser_Period = 4;
		ET_Period = 5;
		EnableSlowEnemy = true; //enable Slow enemy
	}
	if (level == 3) {
		Laser_Period = 3;
		ET_Period = 4;
	}
}

//--------------------------------------------------
/**
initialize the game when launching each time
*/
void Game::initGame() {
	// initialize game variables
	score = 0;
	level = 1;
	Nb_ShipLasers = 0;
	Nb_EnemyLasers = 0;
	Nb_ETs = 0;
	ET_Period = 6;// seconds

	//MYCODE
	Nb_ETs_Slow = 0;
	EnableSlowEnemy = false;
	GameSpeed = 50;
	Laser_Period = 6;
}

//*****************************************************************8
// Constructor --------------------------------------------------
Game::Game()
{
	// initialize game variables
	score = 0;
	level = 1;
	Nb_ShipLasers = 0;
	Nb_EnemyLasers = 0;
	Nb_ETs = 0;
	ET_Period = 6;// seconds

	//MYCODE
	Nb_ETs_Slow = 0;
	EnableSlowEnemy = false;
	GameSpeed = 50;
	Laser_Period = 6;
}

// destructor --------------------------------------
Game::~Game()
{
	// delete the ETs Ennemy_Fast  --------------------------
	for (int i = 1; i <= Nb_ETs; i++) {
		delete ET_List[i - 1];
	}

	// delete the ship lasers --------------------------
	for (int i = 1; i <= Nb_ShipLasers; i++) {
		delete Ship_Lasers[i - 1];
	}

	// delete the enemy lasers --------------------------
	for (int i = 1; i <= Nb_EnemyLasers; i++) {
		delete Enemy_Lasers[i - 1];
	}

	//MYCODE
	//delete the ETs Enemy_Slow
	for (int i = 1; i <= Nb_ETs_Slow; i++) {
		delete ET_List_Slow[i - 1];
	}
}

int Game::getScore() {
	return score;
}

int Game::getLevel() {
	return level;
}

// ---------------------------------------------------------------
// Play() function starts and ends the game
// return: 0=>Game Over, 1=>You win, 2=>You Quit
// type e to quit/exit game
// --------------------------------------------------------------
int Game::Play() {
	initGame();

	unsigned int gameHighScore = 0;
	string PlayerName;
	fstream gameScoreFile("gameData.ini", ios::in); //open the file containing highscore and player name
	if (gameScoreFile.is_open()) {
		std::getline(gameScoreFile, PlayerName); //get the player name
		gameScoreFile >> gameHighScore; //get the highscore
		gameScoreFile.close(); //close the file
	}

	char Key_Pressed; // key pressed by player on keyboard

	//----------------------------------------------------
	// set window dimension 100 columns, 42 lines
	system("CLS");
	UIKit::setWindowDimensions(0, 0, 100, 42);

	string line;
	ifstream gameLogoSmall("gameLogoSmall.txt"); //open the game logo file
	if (gameLogoSmall.is_open())
	{
		UIKit::color(COLOR_BRIGHT_BLUE);
		for (int i = 0; getline(gameLogoSmall, line); i++) { //get each line from the file and print it on screen top right
			UIKit::gotoXY(49, 4 + i);
			cout << line;
		}
		gameLogoSmall.close(); //close the file
	}

	// left game frame with ship etc... 
	// the game field is 40 columns X 40 lines
	// so make the frame around 41 columns, 43 lines, color 15
	UIKit::frame(0, 0, 41, 42, COLOR_BRIGHT_WHITE);

	UIKit::frame(46, 9, 95, 17, COLOR_BRIGHT_WHITE);

	// show the ship
	My_Ship.show();

	//create a 2nd ship by cloning, call the copy constructor;
	//Ship Ship_Nb2(My_Ship);
	//Ship_Nb2.show();

	// create at least 1 ET (Enemy_Fast), those move from left to right
	ET_List[0] = new Enemy_Fast;
	Nb_ETs = 1;
	Create_Enemy_Laser(ET_List[0]->coord.X, ET_List[0]->coord.Y + 1);
	PlaySound(TEXT("sound/enemy_Laser.wav"), NULL, SND_FILENAME | SND_ASYNC);
	last_ET_time = clock();// time when the last ennemy was created
	last_Laser_time = last_ET_time;

	Game_Paused = false;

	// MASTER GAME LOOP ---------------------------------------------
	while (true) {
		Sleep(GameSpeed); // slow down the game loop

		//Read keyboard input -----------------------
		if (_kbhit()) {
			Key_Pressed = _getch();
		}
		else {
			Key_Pressed = 0;
		}

		if (Key_Pressed == 'p' || Key_Pressed == 'P') {
			// pause the game
			Game_Paused = true;
			PlaySound(TEXT("sound/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			UIKit::gotoXY(60, 30);
			cout << "Game Paused!";
			continue; // skip the rest and restart from top of while loop
		}
		else if (Key_Pressed == 0 and Game_Paused) {
			// no key pressed, stay paused
			continue; // skip the rest and restart from top of while loop
		}
		else {
			// key was pressed, resume game
			UIKit::gotoXY(60, 30);
			cout << "            ";
			Game_Paused = false;
		}

		switch (Key_Pressed) {
		case KEY_ESC:
			UIKit::gotoXY(55, 30); //print confirmation message to quit the game
			cout << "Press ESC Again to Quit!";
			PlaySound(TEXT("sound/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			_kbhit();
			Key_Pressed = _getch();

			if (Key_Pressed == KEY_ESC) { //if player press ESC twice quit game
				PlaySound(NULL, 0, 0);
				return(2);// User quit the game before the end
			}
			else {
				UIKit::gotoXY(55, 30);
				cout << "                        "; //for clearing the confirmation message
			}
			break;

		case KEY_SPACE:
			// spacebar ASCII code = 32
			// Create new ship lasers
			// ### TODO
			Ship_Laser_Create();
			break;

		case KEY_LEFT:
		case KEY_RIGHT:
			// Move ship ---------------------------------
			My_Ship.move(Key_Pressed);
			break;
		}
		// end of switch ------------------------------------------
		//Ship_Nb2.show();

		// move the enemy lasers ----------------------------
		// ### TODO
		Enemy_Lasers_Move_All();

		// check if ship killed by enemy fire ---------------
		// ### TODO
		if (Check_Ship_Killed()) return(0);// game over

		// move the ship lasers -----------------------------
		// ### TODO
		Ship_Lasers_Move_All();

		// move the ETs (Enemy_Fast) ------------------------
		// ### TODO
		ETs_Move_All();

		// check ETs killed ---------------------------------
		// ### TODO
		Check_ETs_Killed();

		// Count how many enemies are alive
		// stop game if 15 enemies alive (as per problem requirement)
		// ### TODO
		if (Enemies_Get_Total_Alive() >= 15) {
			return(0); // Game Over
		}

		// Check if all enemies were killed
		// End game or change level
		// ### TODO
		if (Enemies_Check_All_Killed() && level == 4) {
			return(1); // you win
		}

		//Changing Level conditions
		Level_Conditions();

		// periodically create more ETs  ---------------------
		// ### TODO 
		Enemies_Create();

		//periodically create Enemy Lasers ----------------------
		Create_Enemy_Lasers_Periodically();

		// Update game info in the right frame ---------------
		UIKit::color(Game_Info_Color);

		if (gameHighScore < score) {//if New High Score created set the new score as highscore
			gameHighScore = score;
			UIKit::gotoXY(55, 20);
			UIKit::color(COLOR_BRIGHT_YELLOW);
			cout << "NEW HIGHSCORE!!!";
		}

		// level 
		UIKit::gotoXY(55, 10); // print level
		std::cout << "Level    : " << level;

		// score
		UIKit::gotoXY(55, 12); // print score
		std::cout << "Score    : " << score;

		// score
		if (gameHighScore > score) {
			UIKit::gotoXY(55, 14); // print highscore created player name
			std::cout << "Player Name : " << PlayerName;
		}
		else {
			UIKit::gotoXY(55, 14); //if new highscore is created then clear that name
			std::cout << "Player Name :            ";
		}

		// score
		UIKit::gotoXY(55, 16); // print highscore
		std::cout << "HighScore   : " << gameHighScore;
	}

}


