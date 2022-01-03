#include "GameFiles.h"

bool GameFiles::ArgumentValidator(int argc, char* argv[])
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
void GameFiles::FileNameCut() {
	size_t suffixeIndex = filename.find_last_of(".");
	filename = filename.substr(0, suffixeIndex);
}

