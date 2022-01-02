
#include "GameController.h"



int main(int argc, char* argv[])
{
	GameController Game;
	if (GameType::ArgumentsValidator(argc, argv))
	{
		GameType::eType gameType = GameType::GetGameType(argc, argv);
		Game.Run(gameType); // runs game as EX3 the only becuase the only argument is the program name
	}

	return 0;
}




// -load [-silent] (or without silent)
// -save ([-silent] can be added as an argument to save but will not be counted)