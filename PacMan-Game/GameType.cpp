#include "GameType.h"

GameType::eType GameType::GetGameType(int argc, char* argv[])
{
	eType gType = eType::UNDEFINED;
	const char* m_LoadGame = "-load";
	const char* m_SaveGame = "-save";
	const char* m_SilentLoad = "-silent";

	if (argc == 1)
	{
		gType = eType::INTERACTIVE;
	}

	else
	{

		if (strcmp(argv[1], m_LoadGame) == 0)
		{
			if (argc == 3)
			{
				gType = eType::SILENT_LOAD;
			}
			else
			{
				gType = eType::LOAD;
			}

		}

		else if (strcmp(argv[1], m_SaveGame) == 0)
		{
			gType = eType::SAVE;
		}
	}

	return gType;
}