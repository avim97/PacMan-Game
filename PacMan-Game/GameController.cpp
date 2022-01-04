#include "GameController.h"

void GameController::Run()
{
	// do a switch case here that activates a specific game depends on the type (load/load silent/save/interactive)
	// ---------------------------------------------------------


	if (m_GameType == GameType::eType::INTERACTIVE ||
		m_GameType == GameType::eType::SAVE)
	{
		ActivateUserDrivenGame();
	}
	else // LOAD or SILENT_LOAD mode
	{
		ActivateMachineDrivenGame();
	}
}
void GameController::ActivateMachineDrivenGame()
{
	Menu gameMenu;
	bool replay = true;

	while (replay)
	{
		ClearInputBuffer();
		

	}
}
void GameController::ActivateUserDrivenGame()
{
	eUserChoice userChoice = eUserChoice::UNDEFINED;
	bool replay = true;

	while (userChoice != eUserChoice::Exit && replay)
	{
		ClearInputBuffer();

		replay = false;

		PrintLogo(GAME_LOGO);

		m_Menu.Activate();
		userChoice = m_Menu.GetUserChoice();

		switch (userChoice)
		{
		case eUserChoice::NewGame:			CreateNewUserDrivenGame(userChoice); replay = true;  break;

		case eUserChoice::Instructions:		PrintInstructions(); replay = true;		break;

		default:							PrintGoodbyeMessage();		break;

		}

	}
}
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
void GameController::PrintGoodbyeMessage()
{
	clrscr();
	PrintLogo(GOODBYE_LOGO);
}
void GameController::PauseGame(Game* currentGame, bool isSingleGame)
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
			currentGame->SetGameStatus(eGameStatus::EXIT);
			clrscr();
			choice = true;
			break;

		case '2':
			currentGame->SetGameStatus(eGameStatus::NEXT_BOARD);
			clrscr();
			choice = true;
			break;

		case 27:
			clrscr();
			currentGame->PrintBoard(true);
			choice = true;
			break;

		default:
			cout << "Wrong choice, press any key and try again." << endl;
			break;
		}
	}



}
bool GameController::RequestColorMode(Game* game)
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
void GameController::CreateNewUserDrivenGame(eUserChoice& userChoice) // add later user choice from the user as a reference to functions argument
{

	vector<string> filePaths;

	if (!m_BoardFilesService.GetDirectoryFilesNames(filePaths, m_BoardFilesService.GetFileSuffix()))
	{
		userChoice = eUserChoice::UNDEFINED;
	}

	else { // IN SAVE MODE THE USER CAN RUN ONLY ALL EXITING FILES OPTIONS - ADJUST THIS 

		clrscr();

		m_GameMode = RequestGameMode();

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

			if (m_BoardFilesService.RequestBoardFile(filePaths, fileName))
			{
				m_GameFilesService.SetFileName(m_BoardFilesService.GetFileName());
				Game* newGame = m_Factory.Create(fileName, m_GameMode, m_GameType, m_GameFilesService);

				if (color == NULL)
					color = RequestColorMode(newGame);

				if (!color)
					newGame->SetDefaultColor();

				clrscr();

				PlayUserDrivenGame(fileName, newGame, true);

				if (newGame->getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
				}

				else if (newGame->getGameStatus() == eGameStatus::WON)
				{
					Game::userWon(color);
				}

				delete newGame;
			}

			break;
		}

		case  ALL_FILES:
			int lives = 3, score = 0;
			bool color = false;

			for (string& fileName = filePaths[0]; !filePaths.empty() && lives > 0;)
			{
				m_BoardFilesService.RemoveFileSuffix(fileName);
				m_GameFilesService.RemoveFileSuffix(fileName);
				Game* newGame = m_Factory.Create(fileName, m_GameMode, lives, score, m_GameType, m_GameFilesService);
				filePaths.erase(filePaths.begin());

				if (color)
					color = RequestColorMode(newGame);

				else
					newGame->SetDefaultColor();

				PlayUserDrivenGame(fileName, newGame, false);

				if (newGame->getGameStatus() == eGameStatus::LOST)
				{
					Game::userLost(color);
					delete newGame;
					return;
				}

				if (newGame->getGameStatus() == eGameStatus::NEXT_BOARD)
				{
					if (filePaths.empty())
					{
						cout << "No other board found, press any key to exit " << endl;

						while (!_kbhit()) {};

						clrscr();
					}
				}

				if (newGame->getGameStatus() == eGameStatus::EXIT)
				{
					delete newGame;
					return;
				}

				lives = newGame->GetCurrentLives();
				score = newGame->GetTotalScore();
			}

			Game::userWon(color);
			break;
		}
	}
}
bool GameController::CreateNewMachineDrivenGame()
{
	bool loadSucceded = true;
	int lives = 3, score = 0;
	bool color = false;
	vector<string> stepsFilePaths;
	vector<string> boardFilePaths;

	if (!m_GameFilesService.GetDirectoryFilesNames(stepsFilePaths, m_BoardFilesService.GetFileSuffix()))
	{
		cout << "No '.steps' files were found, please load files and run the program again" << endl;
		loadSucceded = false;
	}

	for (string& stepsFileName = stepsFilePaths[0]; !stepsFilePaths.empty() && 
		loadSucceded &&
		lives > 0;)
	{

	}
	
	return loadSucceded;
}
void GameController::PlayUserDrivenGame(string& fileName, Game* game, bool isSingleGame)
{
	eGameStatus KeyPressed = eGameStatus::RUNNING;

	clrscr();

	game->PrintBoard();
	game->initView();

	while (game->getGameStatus() == eGameStatus::RUNNING)
	{
		game->PlayGame();
		KeyPressed = game->getGameStatus();

		if (KeyPressed == eGameStatus::ESC_PRESSED)
		{
			game->SetGameStatus(eGameStatus::RUNNING);
			PauseGame(game, isSingleGame);
		}
	}

}