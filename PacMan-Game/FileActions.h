#pragma once
#include "io_utils.h"
#include <fstream>
#include <string>
#include "eBoardObjects.h"


using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

typedef vector<vector<char>> GameBoard;

class FileActions {
public:
	static bool  DirFileList(vector<string>& fileArr); // moved to FileService
	static void sortBoardFileNames(vector<string>& fileArr); //moved to FileService
	static void updateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH); //need to move to board files
	static bool SpecificFileNameSearch(vector<string>& fileArr, string& fileName); //moved to FileService
};