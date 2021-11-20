#include "GameController.h"


#include <iostream>
using std::cout;

//Run was replaced with menu class
// 
////void GameController::Run()
//{
//	//int userChoice;
//
//	//printMenu(); - same function under menu class
//
//	//cin >> userChoice;
//
//	//switch (static_cast<eUserChoice>(userChoice))
//	//{
//	//case eUserChoice::NewGame:			startNewGame();				break;
//
//	//case eUserChoice::Instructions:		printInstructions();		break;
//
//	//case eUserChoice::Exit:	make a function here that says goodbye;		break;
//
//	//default:	/*print wrong choice message (and show the menu again) ;*/						break;
//
//
//	//}
//
//
//};

void GameController::startNewGame()
{
	Game newGame;

	newGame.printBoard();
	
	newGame.initView();

	while (newGame.getGameStatus() == eGameStatus::RUNNING)
	{
		newGame.PlayGame();
	}



}

//void GameController::printMenu() const {
//
//	cout << "Hello and welcome to PACMAN!";
//	cout << "";
//
//}

// make a method for "printInstruction()"