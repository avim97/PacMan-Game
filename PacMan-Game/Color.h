#pragma once
#include <windows.h>
#include <iostream>
#include "io_utils.h"
class Color
{
public:
	static enum class eColor { BLUE = 1, BOLD_GREEN, CYAN, RED, PURPLE,YELLOW, FAINT_YELLOW = 14, DEFAULT };
private:
	eColor m_currColor;
public:
	Color(eColor color) { m_currColor = color; };
	Color() : m_currColor(eColor::DEFAULT) {};
	void setColor(eColor color) { m_currColor = color; };
	int getColor() { return static_cast<int>(m_currColor); };
	static int getColorValue(eColor color) { return static_cast<int>(color); };
	static void applyOutputColor(int color);
	static void resetOutputColor();
	
};

// we need to change the color of the breadcrumbs and lifes and score to white when chosen no color and in the end to find a
// way to not use the function applyColorOutput at all if the user chose "not colorful" (maybe use inheritence ?)


