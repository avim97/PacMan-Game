#pragma once

#include <iostream>
#include <string>
using std::string;

class GameType
{
public:
	enum class eType{ LOAD, SILENT_LOAD, SAVE, INTERACTIVE, UNDEFINED };

public:

	static eType GetGameType(int argc, char* argv[]);
	static bool ArgumentsValidator(int argc, char* argv[]); 
};

