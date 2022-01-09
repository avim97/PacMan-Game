#pragma once

#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "FileConstants.h"

using std::string;

class Direction
{
public:
	enum class  eDirection { UP = 'W', DOWN = 'X', LEFT = 'A', RIGHT = 'D', STAY = 'S', UNDEFINED = 'N', VALID = 'V' };
	static eDirection Convert(char key);
	static eDirection Convert(string& _direcion);
	static string ConvertToString(char _direction);
	static char ConvertToChar(string& _direction);
	static eDirection getRandDir();
	static bool isValidDirection(char nextDirection);
	static eDirection GetDirection(int move);
};

