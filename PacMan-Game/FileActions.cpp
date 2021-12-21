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
		if (pathStr.size() > 11 && pathStr.size() - 11 == pathStr.rfind(".screen"))
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
void FileActions::updateBoardFromFile(string& fileName, GameBoard& board,int& HEIGHT,int& WIDTH)
{
	string readLine;
	std::ifstream readFile(fileName);
	while (!readFile.eof())
	{
		getline(readFile, readLine);
		vector<char> temp;
		for (char& c : readLine)
		{
			temp.push_back(c);
		}
		board.push_back(temp);
	}
	WIDTH = board[0].size();
	HEIGHT = board.size();
	readFile.close();

}