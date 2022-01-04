#pragma once
#include "FileActions.h"
#include "GameType.h"
#include "FileService.h"
#include "io_utils.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::ofstream;

class GameFiles :public FileService
{
private:
	ofstream m_StepsFile;
	ofstream m_ResultFile;
	string m_FileName;
	const char* m_StepsFileSuffix = ".steps";
	const char* m_ResultFileSuffix = ".result";
	const char* m_BoardFileName = ".screen";

public:
	GameFiles():
		m_StepsFile(),
		m_ResultFile()
	{};

	void RemoveFileSuffix(){};
	void CreateStepsFile() { m_StepsFile.open(m_FileName + ".steps", std::ofstream::trunc); };
	void CreateResultFile() { m_StepsFile.open(m_FileName + ".result", std::ofstream::trunc); };
	void InsertGameColorTOFile(bool isColorful) { m_StepsFile << ("%b", isColorful) << endl; clearInputBuffer(); };
	void InsertStringToStepsFile(string& string) { m_StepsFile << string << endl; clearInputBuffer(); };
	void InsertResultToStepsFile(string& string) { m_ResultFile << string << endl; clearInputBuffer(); };
	void CreateRecordingFiles(string& filename);
};





