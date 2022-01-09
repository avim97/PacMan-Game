#pragma once
#include "FileService.h"
#include "FileConstants.h"

using file_consts::board_file_suffix;

typedef vector<vector<char>> GameBoard;

class BoardFiles: public FileService
{

public:
	const char* GetFileSuffix() const { return board_file_suffix; };
	static void UpdateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH);
	bool RequestBoardFile(vector<string>& totalFiles, string& fileName) ;
};

