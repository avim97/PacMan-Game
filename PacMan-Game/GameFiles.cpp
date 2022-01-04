#include "GameFiles.h"

void GameFiles::CreateRecordingFiles()
{
	CreateStepsFile();
	CreateResultFile();
}

void GameFiles::InsertGameColorToFile(bool isColorful)
{
	stringstream outputString;

	if (isColorful)
		outputString << "COLORFUL GAME";
	else
		outputString << "NOT_COLORFUL GAME";


	m_StepsFile << outputString.rdbuf() << endl;
	ClearInputBuffer();
}

void GameFiles::InsertStringToStepsFile(stringstream& string)
{
	m_StepsFile << string.rdbuf() << endl;
};

void GameFiles::InsertStringToResultFile(stringstream& string)
{
	m_ResultFile << string.rdbuf() << endl;
};