#pragma once
#include "FileService.h"

typedef vector<vector<char>> GameBoard;

class BoardFiles: public FileService
{

private:
	
	const char* m_fileSuffix = ".screen";

public:
	const char* GetFileSuffix() const { return m_fileSuffix; };
	static void UpdateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH);
	bool RequestBoardFile(vector<string>& totalFiles, string& fileName) ;
};

