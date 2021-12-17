#include "FileActions.h"




void FileActions::sortNames(vector<string>& fileArr)
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
		sortNames(fileArr);
	}

}