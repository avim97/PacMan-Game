#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "io_utils.h"
#include "eBoardObjects.h"
#include "Exception.h"


using std::string; using std::vector; 
using std::cout; using std::cin;
using std::endl; using std::char_traits;
using std::sort;
using std::stringstream;

class FileService
{

protected:
	string m_FileName;

public:
	bool GetDirectoryFilesNames(vector<string>& filesNames, const char* file_suffix) ;
	void SortFilesNames(vector<string>& filesNames);
	void RemoveFileSuffix(string& filename);
	void SetFileName(string& filename) { m_FileName = filename; };
	string& GetFileName() { return m_FileName; };
};

