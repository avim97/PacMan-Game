#include "GameController.h"
#include <iostream>

using std::cout;


void GameController::Run(GameType::eType type)
{
	// do a switch case here that activates a specific game depends on the type (load/load silent/save/interactive)
	// ---------------------------------------------------------
	//switch (type)
	//{
	//case GameType::LOAD:
	//	ActivateLoadGame(args here... (add a mode that indicates if silent or not));
	//	break;

	//case GameType::SILENT_LOAD:
	//	ActivateLoadGame(args here(add a mode that indicates if silent or not))

	//case GameType::SAVE:
	//	ActivateRecordingGame(args here....);
	//	break;

	//default: //No argument were entered, meaning the game if gonna be a regular game
	//	PlayUserDrivenGame(args here....);
	//	break;
	//}

	//------------------------------------------------------------------

	eUserChoice userChoice = eUserChoice::UNDEFINED;
	bool replay = true;

	while (userChoice != eUserChoice::Exit && replay)
	{
		clearInputBuffer();

		replay = false;

		PrintLogo(GAME_LOGO);

		userChoice = ActivateMenu();

		switch (userChoice)
		{
		case eUserChoice::NewGame:			ChooseScreenOrVector(userChoice); replay = true;  break;

		case eUserChoice::Instructions:		PrintInstructions(); replay = true;		break;

		default:							PrintGoodbyeMessage();		break;

		}

	}
};

void GameController::PrintInstructions()
{
	clrscr();
	cout << endl;
	cout << " How do you win?" << endl;
	cout << " In order to win the Pacman needs to eat all the spreaded breadcrumbs" << endl;
	cout << " How do you lose?" << endl;
	cout << " You have 3 lives, if a ghost catches you 3 times the game will be over!" << endl;
	cout << " Keys: LEFT a or A, RIGHT d or D, UP w or W, Down x or X, STAY s or S" << endl;
	cout << "            -------------------------------------------              " << endl;
	cout << "           Press any key to go back to the main menu..." << endl;

	while (!_kbhit());
	clrscr();
}
void GameController::PrintLogo(int logo)
{
	clrscr();

	switch (logo) {
	case GAME_LOGO:
		cout << "  _ __   __ _  ___ _ __ ___   __ _ _ __  " << endl;
		Sleep(200);
		cout << " | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ " << endl;
		Sleep(200);
		cout << " | |_) | (_| | (__| | | | | | (_| | | | |" << endl;
		Sleep(200);
		cout << " | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|" << endl;
		Sleep(200);
		cout << " |_|                                     " << endl;


		cout << "         ___            " << endl
			<< "        |||||           " << "       ||||||           \n"
			<< "       | *| *|          " << "      ||||| ||          \n"
			<< "       |||||||          " << "     |||||||            \n"
			<< "      |||||||||         " << "    |||||||      *    * \n"
			<< "     |||||||||||        " << "     |||||||            \n"
			<< "     |_|_|_|_|_|        " << "      ||||||||          \n"
			<< "     | | | | | |        " << "       ||||||           \n"


			<< "\033[37m" << endl;

		break;

	case GOODBYE_LOGO:
		cout << "  _____                 _ _                _   " << endl;
		cout << " / ____|               | | |              | |  " << endl;
		cout << "| |  __  ___   ___   __| | |__  _   _  ___| |  " << endl;
		cout << "| | |_ |/ _ \\ / _ \\ / _` | '_ \\| | | |/ _ \\ |  " << endl;
		cout << "| |__| | (_) | (_) | (_| | |_) | |_| |  __/_|  " << endl;
		cout << " \\_____|\\___/ \\___/ \\__,_|_.__/ \\__, |\\___(_)   " << endl;
		cout << "                                  _/ |               " << endl;
		cout << "                                 |___/               " << endl;
		break;

	}





}
eUserChoice GameController::ActivateMenu()
{
	Menu gameMenu;

	gameMenu.Print();

	while (gameMenu.GetUserChoice() == eUserChoice::UNDEFINED)
	{
		gameMenu.RequestInput();
	}

	return gameMenu.GetUserChoice();
} //Moved to menu class
void GameController::PrintGoodbyeMessage()
{
	clrscr();
	PrintLogo(GOODBYE_LOGO);
}
void GameController::ChooseScreenOrVector(eUserChoice& userChoice) // add later user choice from the user as a reference to functions argument
{

	vector<string> filePaths;

	if (!FileActions::DirFileList(filePaths))
	{
		userChoice = eUserChoice::UNDEFINED;
	} // tranfer this method to FileService class;





	else {

		clrscr();

		GameMode mode = RequestGameMode();

		clrscr();

		cout << "Please choose one of the following:" << endl;
		cout << "(1) Load my own file by name" << endl;
		cout << "(2) Load all existing files " << endl;

		char choice = _getch();

		switch (choice)
		{

		case SPECIFIC_FILE:
		{
			string fileName;
			bool color = NULL;

			if (FileActions::SpecificFileNameSearch(filePaths, fileName))
			{
				Game newGame(fileName, mode);
				if (color == NULL)
					color = RequestColorMode(newGame);

				if (!color)
					newGame.SetDefaultColor();

				clrscr();

				PlayUserDrivenGame(fileName, mode, newGame, true);

				if (newGame.getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
				}

				else if (newGame.getGameStatus() == eGameStatus::WON)
				{
					Game::userWon(color);
				}

			}

			break;
		}

		case  ALL_FILES:
			int lives = 3, score = 0;
			bool color = false;

			for (string& fileName = filePaths[0]; !filePaths.empty() && lives > 0;)
			{
				Game newGame(fileName, mode, lives, score);
				filePaths.erase(filePaths.begin());

				if (color)
					color = RequestColorMode(newGame);

				else
					newGame.SetDefaultColor();

				clrscr();
				newGame.PrintBoard();

				PlayUserDrivenGame(fileName, mode, newGame, false);

				if (newGame.getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
					return;
				}


				if (newGame.getGameStatus() == eGameStatus::NEXT_BOARD)
				{
					if (filePaths.empty())
					{
						cout << "No other board found, press any key to exit " << endl;

						while (!_kbhit()) {};

						clrscr();
					}
				}

				if (newGame.getGameStatus() == eGameStatus::EXIT)
				{
					return;
				}

				lives = newGame.getPacman().GetCurrentLives();
				score = newGame.GetTotalScore();
			}


			Game::userWon(color);
			break;
		}
	}
}
void GameController::PlayUserDrivenGame(string& fileName, GameMode mode, Game& game, bool isSingleGame)
{
	eGameStatus KeyPressed = eGameStatus::RUNNING;

	clrscr();

	game.PrintBoard();

	while (game.getGameStatus() == eGameStatus::RUNNING)
	{
		game.PlayGame();
		KeyPressed = game.getGameStatus();

		if (KeyPressed == eGameStatus::ESC_PRESSED)
		{
			game.SetGameStatus(eGameStatus::RUNNING);
			PauseGame(game, isSingleGame);
		}
	}

}
void GameController::PauseGame(Game& currentGame, bool isSingleGame)
{

	clrscr();
	PrintLogo(GAME_LOGO);

	cout << "Game paused, please choose:" << endl;
	cout << "(1)   Back to main menu " << endl;
	if (!isSingleGame)
	{
		cout << "(2)   Move to the next board " << endl;
	}
	;
	cout << "(Esc) Continue Playing " << endl;


	bool choice = false;
	while (!choice)
	{
		char userchoice = _getch();
		switch (userchoice) {

		case '1':
			currentGame.SetGameStatus(eGameStatus::EXIT);
			clrscr();
			choice = true;
			break;

		case '2':
			currentGame.SetGameStatus(eGameStatus::NEXT_BOARD);
			clrscr();
			choice = true;
			break;

		case 27:
			clrscr();
			currentGame.PrintBoard(true);
			choice = true;
			break;

		default:
			cout << "Wrong choice, press any key and try again." << endl;
			break;
		}
	}



}
bool GameController::RequestColorMode(Game& game)
{
	char colorStyle = 0;
	bool isColorful = true;

	clrscr();

	cout << " Please choose: " << endl << " (1) Colorful " << endl << " (2) Not Colorful " << endl;

	while (colorStyle != '1' && colorStyle != '2')
	{

		colorStyle = _getch();

		if (colorStyle == '2')
		{

			isColorful = false;

		}

		else //wrong input
		{
			cout << "Invalid choice, please choose again." << endl;
		}
	}

	return isColorful;

}
GameMode GameController::RequestGameMode()
{

	GameMode mode = GameMode::UNDEFINED;
	clrscr();

	cout << "Please choose game difficulty:" << endl;
	cout << "(1) Novice" << endl;
	cout << "(2) Good" << endl;
	cout << "(3) Best" << endl;

	while (mode == GameMode::UNDEFINED)
	{
		char choice;
		choice = _getch();
		switch (choice)
		{
		case static_cast<char>(GameMode::NOVICE) + '0':
			mode = GameMode::NOVICE;
			break;

		case static_cast<char>(GameMode::GOOD) + '0':
			mode = GameMode::GOOD;
			break;

		case static_cast<char>(GameMode::BEST) + '0':
			mode = GameMode::BEST;
			break;

		default:
			cout << "Wrong choice, please try again." << endl;
			break;
		}
	}

	return mode;
}
void GameController::ActivateRecordingGame()
{
	Menu gameMenu;
	bool replay = true;
	eUserChoice userChoice = eUserChoice::UNDEFINED;

	while (userChoice != eUserChoice::Exit && replay)
	{
		clearInputBuffer();

		replay = false;

		PrintLogo(GAME_LOGO);

		gameMenu.Activate();
		userChoice = gameMenu.GetUserChoice();

		switch (userChoice)
		{
		case eUserChoice::NewGame:			ChooseScreenOrVector(userChoice); replay = true;  break;

		case eUserChoice::Instructions:		PrintInstructions(); replay = true;		break;

		default:							PrintGoodbyeMessage();		break;

		}

	}
}
