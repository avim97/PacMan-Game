
#include "GameController.h"



int main(int argc, char* argv[])
{

	if (GameType::ArgumentsValidator(argc, argv))
	{
		GameController Game(GameType::GetGameType(argc, argv));
		Game.Run(); 
	}

	return 0;
}
