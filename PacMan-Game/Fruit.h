#pragma once
#include "GameCreature.h"


class Fruit : public GameCreature {
private:
	int m_ScoreValue;
	bool m_IsActive;


public:
	Fruit() :
		GameCreature(
			GetFruitFigure(GetRandomScoreValue()),
			Color::eColor::PURPLE,
			{ 36, 20 },
			static_cast<char>(Direction::eDirection::STAY)),
		m_IsActive(false)
	{};
	int GetScoreValue() const { return m_ScoreValue; };
	bool IsActive() const { return m_IsActive; };
	void ActivateFruit(Position position);
	void DeActivateFruit(Board& board) ;
	int GetRandomScoreValue() { m_ScoreValue = 10 - (1 + rand() % 5); return m_ScoreValue; };
	char GetFruitFigure(int value) const;
	void Erase(const int yCoord, const int xCoord, Board& board) const override;
};