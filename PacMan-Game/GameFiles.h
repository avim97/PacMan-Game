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
	const char* m_StepsFileSuffix = ".steps";
	const char* m_ResultFileSuffix = ".result";
	const char* m_BoardFileName = ".screen";

public:
	GameFiles():
		m_StepsFile(),
		m_ResultFile()
	{};

	void CreateStepsFile() { m_StepsFile.open(m_FileName + ".steps", std::ofstream::trunc); };
	void CreateResultFile() { m_ResultFile.open(m_FileName + ".result", std::ofstream::trunc); };
	void InsertGameColorToFile(bool isColorful); 
	void InsertStringToStepsFile(stringstream& string);
	void InsertStringToResultFile(stringstream& string);
	void CreateRecordingFiles();
	void CloseFiles() { m_StepsFile.close(); m_ResultFile.close(); };
};





