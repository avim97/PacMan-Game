#pragma once
#include "eUserChoice.h"
#include "io_utils.h"


using namespace std;

class Menu {
private:
	eUserChoice m_UserChoice;

public:
	Menu() : m_UserChoice(eUserChoice::UNDEFINED) {};
	void Activate();
	void Print();
	void RequestInput();
	void CheckInput(const char choice);
	eUserChoice GetUserChoice() { return m_UserChoice; };
	void SetUserChoice(eUserChoice choice) { m_UserChoice = choice; };
};
