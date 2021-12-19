#pragma once
#include "io_utils.h"
#include <fstream>
#include <string>


using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

typedef vector<vector<char>> GameBoard;

class FileActions {
public:
	static void dirFileList(vector<string>& fileArr);
	static void sortBoardFileNames(vector<string>& fileArr);
	static void updateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH);
};