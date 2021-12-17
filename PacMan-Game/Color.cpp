#include "Color.h"
Color::eColor Color::getColor(const int colorValue)
{
	eColor color = eColor::DEFAULT;

	switch (colorValue)
	{
	case static_cast<int>(eColor::BLUE):
		color = eColor::BLUE;
		break;

	case static_cast<int>(eColor::BOLD_GREEN):
		color = eColor::BOLD_GREEN;
		break;

	case static_cast<int>(eColor::CYAN):
		color = eColor::CYAN;
		break;

	case static_cast<int>(eColor::RED):
		color = eColor::RED;
		break;

	case static_cast<int>(eColor::PURPLE):
		color = eColor::PURPLE;
		break;

	case static_cast<int>(eColor::YELLOW):
		color = eColor::YELLOW;
		break;

	case static_cast<int>(eColor::FAINT_YELLOW):
		color = eColor::FAINT_YELLOW;
		break;

	default:
			break;

	}

	return color;
}
void Color::applyOutputColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Color::resetOutputColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(eColor::DEFAULT));
	hideCursor();
}


