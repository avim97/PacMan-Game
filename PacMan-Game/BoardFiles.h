#pragma once
#include "FileService.h"

class BoardFiles: public FileService
{
private:
	const char* m_fileSuffix = ".screen";
};

