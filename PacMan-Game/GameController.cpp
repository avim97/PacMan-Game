#include "GameController.h"

void GameController::Run()
{
	if (m_GameType == GameType::eType::INTERACTIVE ||
		m_GameType == GameType::eType::SAVE)
	{
		ActivateUserDrivenGame();
	}
	else // LOAD or SILENT_LOAD mode
	{
		ActivateMachineDrivenGame();
	}

	//COMESTICS - transfer to SWITCH CASE
}
void GameController::ActivateMachineDrivenGame()
{
	CreateNewMachineDrivenGame();
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
	bool isValidChoice = false;
	char inputChoice;

	clrscr();

	PrintLogo(GAME_LOGO);

	cout << "Game paused, please choose:" << endl;

	if (!isSingleGame)
	{
		cout << "(1)   Move to the next board " << endl;
	}

	cout << "(2)   Back to main menu " << endl;
	cout << "(Esc) Continue Playing " << endl;

	while (!isValidChoice)
	{
		inputChoice = _getch();

		switch (inputChoice) {

		case '1':
			currentGame->SetGameStatus(eGameStatus::EXIT);
			clrscr();
			isValidChoice = true;
			break;

		case '2':

			currentGame->SetGameStatus(eGameStatus::NEXT_BOARD);
			clrscr();
			isValidChoice = true;
			break;

		case ESC: //Create ENUM for ESC KEY!!
			currentGame->SetGameStatus(eGameStatus::RUNNING);

			clrscr();
			currentGame->PrintBoard(true);
			isValidChoice = true;
			break;

		default:
			cout << "Wrong choice, press any key and try again." << endl;
			isValidChoice = false;
			break;
		}
	}



}
bool GameController::RequestColorMode()
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
void GameController::RequestBoardLoadingMode(char& choice)
{
	cout << "Please choose one of the following:" << endl;
	cout << "(1) Load my own file by name" << endl;
	cout << "(2) Load all existing files " << endl;

	choice = _getch();
}
void GameController::LoadSpecificBoardFile(vector<string>& filePaths)
{
	string fileName;
	bool color = true;
	color = RequestColorMode();

	if (m_BoardFilesService.RequestBoardFile(filePaths, fileName))
	{
		m_GameFilesService.SetFileName(m_BoardFilesService.GetFileName());
		Game* newGame = m_Factory.Create(fileName, m_GameMode, m_GameType, m_GameFilesService);


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


}
void GameController::CreateNewUserDrivenGame(eUserChoice& userChoice)
{

	vector<string> filePaths;

	if (!m_BoardFilesService.GetDirectoryFilesNames(filePaths, m_BoardFilesService.GetFileSuffix()))
		userChoice = eUserChoice::UNDEFINED;

	else {
		char choice;

		clrscr();

		m_GameMode = RequestGameMode();

		clrscr();

		if (m_GameType == GameType::eType::SAVE)
			choice = ALL_FILES;

		else
			RequestBoardLoadingMode(choice);

		switch (choice)
		{
		case SPECIFIC_FILE:
		{
			LoadSpecificBoardFile(filePaths);
			break;
		}
		case  ALL_FILES:
			LoadAllBoardFiles(filePaths);
			break;
		}
	}
}
void GameController::LoadAllBoardFiles(vector<string>& filePaths)
{
	int lives = 3, score = 0;
	bool color = true;
	color = RequestColorMode();

	eGameStatus game_status = eGameStatus::RUNNING;

	do
	{
		string& file_name = filePaths[0];
		m_BoardFilesService.RemoveFileSuffix(file_name);
		m_GameFilesService.RemoveFileSuffix(file_name);
		Game* newGame = m_Factory.Create(file_name, m_GameMode, lives, score, m_GameType, m_GameFilesService);

		filePaths.erase(filePaths.begin());

		if (!color)
			newGame->SetDefaultColor();

		PlayUserDrivenGame(file_name, newGame, false);
		game_status = newGame->getGameStatus();

		switch (game_status)
		{
		case eGameStatus::LOST:
			Game::userLost(color);
			game_status = eGameStatus::EXIT;
			delete newGame;
			break;

		case eGameStatus::WON:
			lives = newGame->GetCurrentLives();
			score = newGame->GetTotalScore();
			delete newGame;
			break;

		case eGameStatus::NEXT_BOARD:

			if (filePaths.empty())
			{
				//throw no more board exception
				cout << "No other board found, press any key to exit " << endl;
				while (!_kbhit()) {};

				clrscr();
			}

			lives = newGame->GetCurrentLives();
			score = newGame->GetTotalScore();
			break;

		default: // User chose to go back to the main menu
			delete newGame;
			break;
		}

	} while (!filePaths.empty() && lives > 0 && game_status != eGameStatus::EXIT);

	if (game_status == eGameStatus::WON)
	{
		Game::userWon(color);
	}


}
bool GameController::CreateNewMachineDrivenGame()
{
	bool loadSucceded = true;
	int lives = 3, score = 0;
	bool color = false;
	vector<string> stepsFilePaths;
	vector<string> boardFilePaths;
	eGameStatus game_status = eGameStatus::RUNNING;

	if (!m_BoardFilesService.GetDirectoryFilesNames(boardFilePaths, m_BoardFilesService.GetFileSuffix()))
	{
		loadSucceded = false;
	}


	do
	{
		string& file_name = boardFilePaths[0];
		m_BoardFilesService.RemoveFileSuffix(file_name);
		m_GameFilesService.RemoveFileSuffix(file_name);
		Game* newGame = m_Factory.Create(file_name, m_GameMode, lives, score, m_GameType, m_GameFilesService);

		boardFilePaths.erase(boardFilePaths.begin());

		if (m_GameType != GameType::eType::SILENT_LOAD)
		{
			newGame->PrintBoard();
			newGame->initView();
		}

		newGame->PlayGame();

	} while (!boardFilePaths.empty() && lives > 0);

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
			PauseGame(game, isSingleGame);
		}
	}

}