#pragma once
#include "FileActions.h"
#include "GameType.h"
#include "FileService.h"
#include "io_utils.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios_base;


class GameFiles :public FileService
{
private:
	fstream m_StepsFile;
	fstream m_ResultFile;
	const char* m_StepsFileSuffix = ".steps";
	const char* m_ResultFileSuffix = ".result";
	const char* m_BoardFileName = ".screen";

public:
	GameFiles():
		m_StepsFile(),
		m_ResultFile()
	{};

	void CreateStepsFile() { m_StepsFile.open(m_FileName + m_StepsFileSuffix, ios_base::out|ios_base::trunc); };
	void CreateResultFile() { m_ResultFile.open(m_FileName + m_ResultFileSuffix, ios_base::out | ios_base::trunc); };
	void InsertGameColorToFile(bool isColorful); 
	void OpenStepsFile() { m_StepsFile.open(m_FileName + m_StepsFileSuffix, ios_base::in); };
	void OpenResultFile() { m_ResultFile.open(m_FileName + m_ResultFileSuffix, ios_base::in); };
	void InsertStringToStepsFile(stringstream& string);
	void InsertStringToResultFile(stringstream& string);
	void CreateRecordingFiles();
	void OpenRecordingFiles();
	string GetStepsFileLine();
	string GetResultFileLine();
	void CloseFiles() { m_StepsFile.close(); m_ResultFile.close(); };
};





