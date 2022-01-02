#pragma once
#include "FileActions.h"
#include "GameType.h"

class GameFiles :public FileActions
{
private:
	const char* m_StepsFileSuffix = ".steps";
	const char* m_ResultFileSuffix = ".result";

public:
	static bool ArgumentValidator(int argc, char* argv[]); //this function validates the command line arguments

};

