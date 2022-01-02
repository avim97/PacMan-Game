#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "io_utils.h"
#include "eBoardObjects.h"

using std::string; using std::vector; 
using std::cout; using std::cin;
using std::endl; using std::char_traits;
using std::sort;

class FileService
{
public:
	bool GetDirectoryFilesNames(vector<string>& filesNames, const char* file_suffix) ;
	void SortFilesNames(vector<string>& filesNames);
	bool FindFile(vector<string>& totalFiles, string& fileName, const char* file_suffix) const ;
};

