#include "GameController.h"


#include <iostream>
using namespace std;

void GameController::Run()
{
	int userChoice;

	printMenu();

	cin >> userChoice;

	switch (static_cast<eUserChoice>(userChoice))
	{
	case eUserChoice::NewGame:			startNewGame();				break;

	case eUserChoice::Instructions:		printInstructions();		break;

	//case eUserChoice::Exit:	make a function here that says goodbye;		break;

	default:	/*print wrong choice message (and show the menu again) ;*/						break;


	}


};

void GameController::startNewGame()
{
	Game newGame;

	newGame.printBoard();
	// add a method in class Game to print lives left below the maze (also foor the score) and update them accordinly
	newGame.initView();

	//........
}


// make a method for "printInstruction()"