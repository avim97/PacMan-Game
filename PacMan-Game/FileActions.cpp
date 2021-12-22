#include "FileActions.h"




void FileActions::sortBoardFileNames(vector<string>& fileArr)
{
	sort(fileArr.begin(), fileArr.end());

}

bool FileActions::DirFileList(vector<string>& fileArr)
{
	string pathStr;
	
	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		pathStr = entry.path().filename().string();
		if (pathStr.size() > 7 && pathStr.size() - 7 == pathStr.rfind(".screen"))
			fileArr.push_back(pathStr);
	}
	if (fileArr.empty())
	{
		clrscr();
		cout << "No suitable files found. Please load Files to project folder and try again." << endl;
		cout << "Press any key to get back to menu." << endl;
		while (!_kbhit());
		clrscr(); 
		return false;
	}
	else
	{
		sortBoardFileNames(fileArr);
		return true;
	}

}
void FileActions::updateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH)
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

bool FileActions::SpecificFileNameSearch(vector<string>& fileArr, string& fileName)
{
	if (std::find(fileArr.begin(), fileArr.end(), fileName) != fileArr.end())
		return true;
	else
		false;
}
