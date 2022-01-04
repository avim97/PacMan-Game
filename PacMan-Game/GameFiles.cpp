#include "GameFiles.h"

void GameFiles::CreateRecordingFiles(string& filename)
{
	RemoveFileSuffix();
	CreateStepsFile();
	CreateResultFile();
}