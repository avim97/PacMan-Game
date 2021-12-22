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
	bool firstRow = true;
	string readLine;
	std::ifstream readFile(fileName);
	while (!readFile.eof())
	{
		getline(readFile, readLine);
		if (firstRow)
		{
			WIDTH = readLine.length();
			firstRow = false;
		}

		vector<char> temp;
		for (int i = 0; i < WIDTH && i < readLine.length(); i++)
		{
			temp.push_back(readLine[i]);
		}
		if (temp.size() < WIDTH)
			while (temp.size() < WIDTH)
				temp.push_back(static_cast<char>(BoardObjects::FOOD));

		board.push_back(temp);
	}

	HEIGHT = board.size();
	readFile.close();

}

bool FileActions::SpecificFileNameSearch(vector<string>& fileArr, string& fileName)
{
	clrscr();
	cout << "Please type in a file name as follows (no spaces): filename.screen " << endl;

	getline(cin, fileName);

	if (std::find(fileArr.begin(), fileArr.end(), fileName) != fileArr.end())
		return true;

	else
		return false;
}
