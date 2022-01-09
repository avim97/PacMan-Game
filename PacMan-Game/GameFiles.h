#pragma once
#include "GameType.h"
#include "FileService.h"
#include "FileConstants.h"
#include "io_utils.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>


using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::stringstream;
using namespace file_consts;

class GameFiles :public FileService
{
private:
	fstream m_StepsFile;
	fstream m_ResultFile;

private:
	enum { MIN_INDEX = 0, MAX_INDEX = 3 };

public:
	GameFiles():
		m_StepsFile(),
		m_ResultFile()
	{};

	void CreateStepsFile() { m_StepsFile.open(m_FileName + steps_file_suffix, ios_base::out|ios_base::trunc); };
	void CreateResultFile() { m_ResultFile.open(m_FileName + result_file_suffix, ios_base::out | ios_base::trunc); };
	void InsertGameColorToFile(bool isColorful); 
	void OpenStepsFile() { m_StepsFile.open(m_FileName + steps_file_suffix, ios_base::in); };
	void OpenResultFile() { m_ResultFile.open(m_FileName + result_file_suffix, ios_base::in); };
	void InsertStringToStepsFile(stringstream& string);
	void InsertStringToResultFile(stringstream& string);
	void CreateRecordingFiles();
	void OpenRecordingFiles();
	string GetStepsFileLine();
	string GetResultFileLine();
	void CloseFiles() { m_StepsFile.close(); m_ResultFile.close(); };
	bool IsStepsFileGood() { return m_StepsFile.good(); };
	bool IsResultFileGood() { return m_ResultFile.good(); };
};





