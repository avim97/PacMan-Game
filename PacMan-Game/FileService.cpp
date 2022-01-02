#include "FileService.h"

bool FileService::GetDirectoryFilesNames(vector<string>& filesNames, const char* file_suffix) 
{
	string pathStr;
	bool namesArrayCreates = false;

	for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
	{
		int suffix_size = char_traits<char>::length(file_suffix);
		pathStr = entry.path().filename().string(); 

		if (pathStr.size() > suffix_size && pathStr.size() - suffix_size == pathStr.rfind(file_suffix))
			filesNames.push_back(pathStr);
	}

	if (filesNames.empty())
	{
		clrscr();
		cout << "No suitable files found. Please upload the required files to working directory and try again." << endl;
		cout << "Press any key to go back to the main menu." << endl;
		if (_kbhit())
		{
			clrscr();
		}
	}

	else
	{
		SortFilesNames(filesNames);
		namesArrayCreates = true;
	}

	return namesArrayCreates;
}

void FileService::SortFilesNames(vector<string>& filesNames)
{
	sort(filesNames.begin(), filesNames.end());
}

bool FileService::FindFile(vector<string>& totalFiles, string& fileName, const char* file_suffix) const
{
	bool fileFound = false;
	clrscr();
	cout << "Please type in a file name as follows (no spaces): filename" << file_suffix << endl;

	getline(cin, fileName);

	if (std::find(totalFiles.begin(), totalFiles.end(), fileName) != totalFiles.end())
		fileFound = true;

	else
	{
		cout << "file not found, press any key to get back to menu" << endl;
		while (!_kbhit()) {};
		clrscr();
	}

	return fileFound;
}