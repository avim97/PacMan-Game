#pragma once
#include "FileActions.h"
#include "GameType.h"
#include "FileService.h"
#include "io_utils.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

class GameFiles :public FileService
{
private:
	std::ofstream Stepsfile;
	std::ofstream Resultfile;
	string& filename;
	const char* m_StepsFileSuffix = ".steps";
	const char* m_ResultFileSuffix = ".result";
	const char* m_BoardFileName = ".screen";

public:

	GameFiles(string& filename) :filename(filename) { FileNameCut(); StepsFileCreation(); ResultFileCreation(); };
	static bool ArgumentValidator(int argc, char* argv[]); //this function validates the command line arguments
	void FileNameCut();
	void StepsFileCreation() { Stepsfile.open(filename + ".steps", std::ofstream::trunc); };
	void ResultFileCreation() { Stepsfile.open(filename + ".result", std::ofstream::trunc); };
	void InsertGameColorTOFile(bool isColorful) { Stepsfile << ("%b", isColorful)<<endl; clearInputBuffer(); };
	void InsertStringToStepsFile(string& string) { Stepsfile << string << endl; };
	void InsertResultToStepsFile(string& string) { Resultfile << string << endl; };
	
};



