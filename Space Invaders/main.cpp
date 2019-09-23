#include <iostream>
#include <fstream>
#include <string>
#include "UIKit.h"
#include "Menu.h"
#include "Game.h"

using namespace std;

void Help() { //Help Menu

	string line;
	ifstream gameLogo("gameLogo.txt"); //Opening Game Logo file

	system("CLS");
	UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); //creating a frame
	if (gameLogo.is_open()) //only perform if the file is open
	{
			UIKit::color(COLOR_BRIGHT_LBLUE);
			for (int j = 0; getline(gameLogo, line); j++) { // Print each line in the file
				UIKit::gotoXY(15, 2 + j);
				cout << line << '\n';
			}		
		gameLogo.close(); //close the file after usage
	}

	UIKit::frame(18, 9, 100, 23, COLOR_BRIGHT_PURPLE); // creating inside frame
	UIKit::gotoXY(45, 9);
	cout << (char)203; //printing the first char of separator
	for (int i = 0; i < 13; i++)// creating the vertical line
	{
		UIKit::gotoXY(45, 10 + i);
		cout << (char)186;
	}
	UIKit::gotoXY(45, 23);
	cout << (char)202;//printing the last char of separator

	UIKit::color(11);
	UIKit::gotoXY(26, 11);
	cout << "LEFT ARROW" << endl;
	UIKit::gotoXY(26, 13);
	cout << "RIGHT ARROW" << endl;
	UIKit::gotoXY(26, 15);
	cout << "SPACE" << endl;
	UIKit::gotoXY(26, 17);
	cout << "P" << endl;
	UIKit::gotoXY(26, 19);
	cout << "ESC" << endl;
	
	//DESCRIPTION 
	UIKit::gotoXY(65, 11);
	cout << "MOVE LEFT " << endl;
	UIKit::gotoXY(65, 13);
	cout << "MOVE RIGHT" << endl;
	UIKit::gotoXY(65, 15);
	cout << "FOR SHOOT THE ENEMIES" << endl;
	UIKit::gotoXY(65, 17);
	cout << "PAUSE THE GAME" << endl;
	UIKit::gotoXY(65, 19);
	cout << "EXIT THE GAME" << endl;
	UIKit::gotoXY(45, 25);
	system("pause");
	return;
}

void about() {
	system("CLS");

	string line;
	ifstream gameLogo("gameLogo.txt"); //opeing game logo file

	system("CLS");
	UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); //creating a frame
	if (gameLogo.is_open()) //only perform operation if file is open
	{
		UIKit::color(COLOR_BRIGHT_LBLUE);
		for (int j = 0; getline(gameLogo, line); j++) { // print each line from the file till EOF
			UIKit::gotoXY(15, 2 + j);
			cout << line << '\n';
		}
		gameLogo.close(); //close the file
	}

	UIKit::frame(18, 9, 100, 23, COLOR_BRIGHT_PURPLE); //creating inside frame

	UIKit::color(0xF);
	UIKit::gotoXY(53, 11);
	cout << "CREATED BY" << endl;

	UIKit::gotoXY(35, 15);
	cout << "MONIKA RANI     CHRISTY THOMAS     KARAMJIT KAUR" << endl;
	UIKit::gotoXY(34, 22);
	cout << "2019-2020 Space Invaders Inc. All Rights Reserved.";

	UIKit::gotoXY(45, 25);
	system("pause");
	return;
}

void saveScore(int score) { //For saving the high score 
	string PlayerName;
	ofstream gameScoreFile("gameData.ini"); //opening the Game score file (write only)
	UIKit::gotoXY(43, 22);
	cout << "ENTER YOUR NAME : ";
	cin >> PlayerName;
	if (gameScoreFile.is_open()) { //only save if the file is available
		gameScoreFile << PlayerName << endl;
		gameScoreFile << score;
		gameScoreFile.close();
	}
}

void winGame(int score,int level, unsigned int gameHighScore) {
	PlaySound(TEXT("sound/win.wav"), NULL, SND_FILENAME | SND_ASYNC);
	string line;
	ifstream winLogo("winLogo.txt"); //opening the wining game Logo file (read only mode)
	if (winLogo.is_open()) //if file is open
	{
		for (int i = 9; i < 15; i++) {//outer loop change color
			UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE);
			UIKit::color(i);
			for (int j = 0; getline(winLogo, line); j++) { //inner loop print all the lines in the file
				UIKit::gotoXY(35, 5 + j);
				cout << line << '\n';
			}
			if (score > gameHighScore) { //if the new score is Highscore
				UIKit::gotoXY(48, 16);
				cout << "NEW HIGHSCORE!!!!";
			}
			winLogo.clear(); //clearing the the EOF flag in the file pointer after reading the end of file
			winLogo.seekg(0, ios::beg); //moving the file pointer to the starting position of the file
			Sleep(200); //small delay for make it animate
			system("CLS");
		}
		UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); 
		UIKit::color(COLOR_BRIGHT_GREEN); //For printing the Last Win Logo as Green
		for (int j = 0; getline(winLogo, line); j++) {
			UIKit::gotoXY(35, 5 + j);
			cout << line << '\n';
		}
		winLogo.close(); //Close the file
	}
	UIKit::gotoXY(54, 18);
	cout << score;
	UIKit::gotoXY(50, 20);
	cout << "LEVEL : " << level;

	if (score > gameHighScore) { //printing only if the score is new highscore
		UIKit::gotoXY(48, 16);
		cout << "NEW HIGHSCORE!!!!";
		saveScore(score); //saving the new highscore
	}

	UIKit::gotoXY(45, 25);
	system("pause");
	PlaySound(NULL, 0, 0);
}
void loseGame(int score,int level, unsigned int gameHighScore) {
	PlaySound(TEXT("sound/lose.wav"), NULL, SND_FILENAME | SND_ASYNC);
	string line;
	ifstream loseLogo("loseLogo.txt"); //opeing the Lose Logo file (read only mode)
	if (loseLogo.is_open()) //if the file is open perform operation
	{
		system("CLS");
		UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); //print the frame
		UIKit::color(COLOR_BRIGHT_RED);
		for (int j = 0; getline(loseLogo, line); j++) { //print each lines from the file
			UIKit::gotoXY(35, 5 + j);
			cout << line << '\n';
		}
		loseLogo.close(); //close the file
	}
	UIKit::gotoXY(54, 18);
	cout << score;
	UIKit::gotoXY(50, 20);
	cout << "LEVEL : " << level;

	if (score > gameHighScore) { //printing the highscore if the new score is highscore
		UIKit::gotoXY(48, 16);
		cout << "NEW HIGHSCORE!!!!";
		saveScore(score);
	}

	UIKit::gotoXY(45, 25);
	system("pause");
	PlaySound(NULL, 0, 0);
}

void quitGame(int score, int level, unsigned int gameHighScore) {
	string line;
	ifstream quitLogo("quitLogo.txt"); //opeing quit logo from file (read only mode)
	if (quitLogo.is_open()) //perform operation only if the file is open
	{
		system("CLS");
		UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); //creating frame
		UIKit::color(COLOR_BRIGHT_LBLUE);
		for (int j = 0; getline(quitLogo, line); j++) { //print each line from the file till EOF
			UIKit::gotoXY(17, 5 + j);
			cout << line << '\n';
		}
		quitLogo.close(); //close the file
	}
	UIKit::gotoXY(45, 25);
	system("pause");
}

int main() {
	int Selection;
	UIKit::visibleCursor(false); //setting the typing cursor as disabled
	string line;

	PlaySound(TEXT("sound/intro.wav"), NULL, SND_FILENAME | SND_ASYNC);
	ifstream gameLogo("gameLogo.txt"); //opeing the Game Logo file (read only mode)
	if (gameLogo.is_open()) //only if the file is open perform operation 
	{
		for (int i = 9; i < 15; i++) { //outer loop with changing colors

			UIKit::color(i);
			for (int j = 0; getline(gameLogo, line); j++) { //inner loop with file printing
				UIKit::gotoXY(10, 10 + j);
				cout << line << '\n';
			}
			gameLogo.clear(); //clear the EOF flag in the file pointer when it reaches the end of the file
			gameLogo.seekg(0, ios::beg); //moving the file pointer to the strating position of the file
			Sleep(500); //small delay to make it animate
			system("CLS");
		}
	}

	unsigned int gameHighScore = 0;
	string PlayerName;
	fstream gameScoreFile; 

	Game new_game;
	int game_result;

	// Create main menu, 3 items, top left corner on line 5, column 8;
	// see Menu.h
	string Choices[] = { "PLAY","HELP","ABOUT","EXIT" };
	Menu Main_Menu("", Choices, 4, 10, 50);

	while(true) {
		system("CLS");
		UIKit::frame(0, 0, 118, 28, COLOR_BRIGHT_PURPLE); //creating the frame
		UIKit::color(COLOR_BRIGHT_LBLUE);
		for (int j = 0; getline(gameLogo, line); j++) { //printing the logo from the file
			UIKit::gotoXY(11, 3 + j);
			cout << line << '\n';
		}
		gameLogo.clear(); //clearing the EOF flag
		gameLogo.seekg(0, ios::beg); //moving file pointer to starting position
		Selection = Main_Menu.displayMenu(); //displaying the menu
		
		switch (Selection) {
		case 1:
			// play the game
			game_result = new_game.Play();

			// ### TODO Better display after game
			//
			gameScoreFile.open("gameData.ini", ios::in); //opeing the Highscore from the file (read only mode)
			if (gameScoreFile.is_open()) {
				std::getline(gameScoreFile, PlayerName); //getting the player name
				gameScoreFile >> gameHighScore; //getting highscore
				gameScoreFile.close(); //close the file
			}
			UIKit::setWindowDimensions(0, 0, 119, 29); //reseting the game Window domension after returning from playing the game
			switch (game_result) {
			case 0:
				//lose condition
				loseGame(new_game.getScore(), new_game.getLevel(), gameHighScore);
				break;
			case 1:
				//win condition
				winGame(new_game.getScore(), new_game.getLevel(), gameHighScore);
				break;
			case 2:
				//quit condition
				quitGame(new_game.getScore(), new_game.getLevel(), gameHighScore);
				break;
			}
			break;
		case 2:
			// display help
			Help();
			break;
		case 3:
			//display abot
			about();
			break;
		case 4:
			// end program
			exit(0);
			break;
		}
	}
	gameLogo.close(); //closing the game logo file;
	return(0);
}