#pragma once

#include "GameCreature.h"


class Ghost : public GameCreature {
	//enum class eMode { BEST = 1, GOOD, NOVICE, UNDEFINED };
	//eMode m_mode;
public:
	Ghost(Color::eColor COLOR, Position _position) :
		GameCreature(
			static_cast<int>(BoardObjects::GHOST),
			COLOR,
			_position,
			static_cast<char>(Direction::eDirection::STAY))
	{};
	void Erase(const int yCoord, const int xCoord, Board& board) const override;

};