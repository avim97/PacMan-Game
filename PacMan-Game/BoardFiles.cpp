#include "BoardFiles.h"

void BoardFiles::UpdateBoardFromFile(string& fileName, GameBoard& board, int& HEIGHT, int& WIDTH)
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


bool BoardFiles::RequestBoardFile(vector<string>& totalFiles, string& fileName)
{
	bool fileFound = false;
	clrscr();
	cout << "Please type in a file name as follows (no spaces): filename" << GetFileSuffix() << endl;

	getline(cin, fileName);

	if (std::find(totalFiles.begin(), totalFiles.end(), fileName) != totalFiles.end())
	{
		RemoveFileSuffix(fileName);
		fileFound = true;
	}

	else
	{
		//throw expected file not found exception (wrong user input?)
		cout << "file not found, press any key to get back to menu" << endl;
		while (!_kbhit()) {};
		clrscr();
	}

	return fileFound;
}