#pragma once

#include <iostream>
#include <string>

class GameType
{
public:
	enum class eType{ LOAD, SILENT_LOAD, SAVE, INTERACTIVE, UNDEFINED };

public:
	static eType GetGameType(int argc, char* argv[]);

};

