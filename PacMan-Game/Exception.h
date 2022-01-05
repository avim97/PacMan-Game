#pragma once
#include "io_utils.h"
using std::string;

class Exception : public std::exception{
private:
	string m_msg;
public:
	Exception(const std::string& msg) : m_msg(msg) {}
	virtual const char* what() const noexcept override
	{
		return m_msg.c_str();
	}
};