#pragma once
#include "io_utils.h"


using std::cout; using std::cin;
using std::endl; using std::string;
using std::vector;

class FileActions {
public:
	static void dirFileList(vector<string>& fileArr);
	static void sortNames(vector<string>& fileArr);
};