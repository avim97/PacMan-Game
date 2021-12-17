#include "FileActions.h"




void FileActions::sortBoardFileNames(vector<string>& fileArr)
{
	sort(fileArr.begin(), fileArr.end());

}

void FileActions::dirFileList(vector<string>& fileArr)
{
	string pathStr;
	vector<string> screen_files;
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		pathStr = entry.path().filename().string();
		if (pathStr.size() > 11 && pathStr.size() - 11 == pathStr.rfind(".screen.txt"))
			fileArr.push_back(pathStr);
	}
	if (screen_files.empty())
	{
		return;//display message about missing files
	}
	else
	{
		sortBoardFileNames(fileArr);
	}

}
void FileActions::updateBoardFromFile(string& fileName, gameBoard& board, int& ROWS, int& COLS)
{
	string readLine;
	int rowNum = 0, colsNum = 0;

	std::ifstream readFile(fileName);
	while (getline(readFile, readLine))
	{
		for (char& c : readLine)
		{
			board[rowNum].push_back(c);
			if (rowNum == 0)
				colsNum++;
		}
		rowNum++;
	}
	ROWS = rowNum + 1;
	COLS = colsNum + 1;
}