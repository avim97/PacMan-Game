#pragma once
#include <windows.h>
#include <iostream>

class Color
{
public:
	enum class eColor { White, Yellow, Blue, Green, Red };
private:
	const char* m_colorCodes[5] = { "\033[1m\033[37m" , "\033[1m\033[33m" ,"\033[1m\033[34m", "\033[1m\033[32m", "\033[1m\033[31m" };
	eColor m_currColor = eColor::White;
public:
	Color(eColor color) { m_currColor = color; };
	void setColor(eColor color) { m_currColor = color; };
	eColor getColor() { return m_currColor; };
	const char* getColorCode(eColor color) { return m_colorCodes[(int)color]; };
	void applyOutputColor(eColor color);
};



