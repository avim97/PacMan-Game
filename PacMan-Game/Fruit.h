#pragma once
#include "GameCreature.h"


class Fruit : public GameCreature {
private:
	int m_ScoreValue;
	bool m_IsActive;


public:
	Fruit(Position initialPosition) :
		GameCreature(
			GetFruitFigure(GetRandomScoreValue()),
			Color::eColor::PURPLE,
			initialPosition,
			static_cast<char>(Direction::eDirection::STAY)),
		m_IsActive(true)
	{};
	int GetScoreValue() const { return m_ScoreValue; };
	bool IsActive() const { return m_IsActive; };
	void ActivateFruit(Position position);
	void DeActivateFruit(Board& board) ;
	void SetActivationMode(bool actived) { m_IsActive = actived; };
	int GetRandomScoreValue() { m_ScoreValue = 10 - (1 + (rand() % 5)); return m_ScoreValue; };
	char GetFruitFigure(int value) const;
	void Erase(const int yCoord, const int xCoord, Board& board) const override;
};