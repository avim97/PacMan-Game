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
bool GameType::ArgumentsValidator(int argc, char* argv[])
{
	bool areValid = true;
	const char* m_LoadGame = "-load";
	const char* m_SaveGame = "-save";
	const char* m_SilentLoad = "-silent";

	for (int i = 1; i < argc && areValid; i++)
	{
		switch (i)
		{
		case 1:
			if (strcmp(argv[i], m_LoadGame) != 0 && strcmp(argv[i], m_SaveGame) != 0)
				areValid = false;
			break;
		case 2:
			if (strcmp(argv[i], m_SilentLoad) != 0)
				areValid = false;
			break;

		default: // there are more than 3 argument (max arguments needed)
			areValid = false;
			break;
		}

	}

	return areValid;
}