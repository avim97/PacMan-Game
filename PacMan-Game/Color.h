#pragma once
#include <windows.h>
#include <iostream>
#include "io_utils.h"

class Color
{
public:
	enum class eColor { BLUE = 1, BOLD_GREEN, CYAN, RED, PURPLE, YELLOW, FAINT_YELLOW = 14, DEFAULT };
private:
	eColor m_currColor;
public:
	Color(eColor color) { m_currColor = color; };
	Color() : m_currColor(eColor::DEFAULT) {};
	void setColor(Color::eColor color) { m_currColor = color; };
	int getColor() const { return static_cast<int>(m_currColor); };
	static eColor getColor(const int colorValue);
	static int getColorValue(eColor color) { return static_cast<int>(color); };
	static void applyOutputColor(int color);
	static void resetOutputColor();

};

