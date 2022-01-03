#pragma once
#include "GameCreature.h"
#include "MovementFactory.h"

class Ghost : public GameCreature {
	GameMode m_mode;
	Movement* m_Movement;
	MovementFactory m_Factory;
public:
	Ghost(Color::eColor COLOR, Position _position, GameMode _mode, int _height, int _width) :
		GameCreature(
			static_cast<char>(BoardObjects::GHOST),
			COLOR,
			_position,
			static_cast<char>(Direction::eDirection::STAY)),
		m_mode(_mode)
	{
		AssignMovement(_mode, _height, _width);
	};

	~Ghost() { delete m_Movement; };
	void AssignMovement(GameMode _mode, int _height, int _width) { m_Movement = m_Factory.Create(_mode, _height, _width); };
	void Erase(const int yCoord, const int xCoord, Board& board) const override;
	Direction::eDirection GetMovement(GameBoard board, int ghostInd, const Position& destination, const Position& source, PositionsVector ghostsPositions, int& ghostsMoves) { return m_Movement->GetMove(board, ghostInd, destination, source, ghostsPositions, ghostsMoves); };
};