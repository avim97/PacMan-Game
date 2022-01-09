
#include "GameController.h"



int main(int argc, char* argv[])
{

	if (GameType::ArgumentsValidator(argc, argv))
	{
		GameController Game(GameType::GetGameType(argc, argv));
		Game.Run(); 
	}

	else
	{
		cout << "Incorrect program arguments" << endl << endl;
		cout << "Usage: " << argv[0] << "[-save] OR [-load | -load silent]" << endl;
	}

	return 0;
}
