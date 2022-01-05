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

		//throw exception for no files found
		clrscr();
		throw Exception("No suitable files found. Please upload the required files to working directory and try again.");
		/*cout << "No suitable files found. Please upload the required files to working directory and try again." << endl;
		cout << "Press any key to go back to the main menu." << endl;
		if (_kbhit())
		{
			clrscr();
		}*/
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

void FileService::RemoveFileSuffix(string& filename)
{
	size_t pos = filename.find_first_of('.');
	m_FileName = filename.substr(0, pos);
}