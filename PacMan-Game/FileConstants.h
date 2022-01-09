#pragma once

namespace file_consts
{
	//--------------------------------------- GAME CREATURES NAME
	inline static const char* pacman = " PACMAN ";
	inline static const char* ghost = " GHOST ";
	inline static const char* fruit = " FRUIT ";

	//--------------------------------------- GAME CREATURES ACTIONS
	inline static const char* move_down = " DOWN ";
	inline static const char* move_up = " UP ";
	inline static const char* move_left = " LEFT ";
	inline static const char* move_right = " RIGHT ";
	inline static const char* move_stay = " STAY ";
	inline static const char* action_deActivation = " DEACTIVATE ";
	inline static const char* action_initialization = " INIT ";
	inline static const char* invalid_action = "INVALID_ACTION";

	//--------------------------------------- LINE DELIMITERS
	inline static const char separator = '|';
	inline static const char hyphen = '-';
	inline static const char space = ' ';
	inline static const char colon = ':';
	inline static const char comma = ',';
	inline static const char left_bracket = '(';
	inline static const char right_bracket = ')';
	inline static const char endline = '\n';

	//----------------------------------------  GAME RESULTS
	inline static const char* NoResult = "NO_RESULT";
	inline static const char* BoardFinishedResult = "BOARD_FINISHED ";
	inline static const char* IntersectionResult = "INTERSECTION ";
	inline static const char* ExitResult = "EXIT ";
	inline static const char* LostResult = "LOST ";

	//----------------------------------------- FILE SUFFIXES
	inline static const char* steps_file_suffix = ".steps";
	inline static const char* result_file_suffix = ".result";
	inline static const char* board_file_suffix = ".screen";
}