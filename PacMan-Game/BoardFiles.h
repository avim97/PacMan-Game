#pragma once
#include "FileService.h"

class BoardFiles: public FileService
{
private:
	const char* m_fileSuffix = ".screen";

public:
	const char* GetFileSuffix() const { return m_fileSuffix; };
};

