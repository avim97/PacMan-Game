#pragma once
#include "GameCreature.h"
#include "MovementFactory.h"

class Ghost : public GameCreature {
	GameMode m_mode;
	Movement* m_Movement;
public:
	Ghost(Color::eColor COLOR, Position _position, GameMode _mode) :
		GameCreature(
			static_cast<char>(BoardObjects::GHOST),
			COLOR,
			_position,
			static_cast<char>(Direction::eDirection::STAY)),
		m_mode(_mode)
	{
		AssignMovement(_mode);
	};

	~Ghost() { delete m_Movement; };
	void AssignMovement(GameMode _mode) { m_Movement = MovementFactory::Create(_mode); }
	void Erase(const int yCoord, const int xCoord, Board& board) const override;
	Direction::eDirection GetMovement(char* board[], int ghostInd, Position& destination, Position* source) { return m_Movement->GetMove(board, ghostInd, destination, source); };
};