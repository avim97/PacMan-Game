#pragma once
#include "GameCreature.h"


class Fruit : public GameCreature {
private:
	int m_ScoreValue;
	bool m_IsActive;
	bool m_ActivationChange;

public:
	Fruit(Position initialPosition) :
		GameCreature(
			GetFruitFigure(GetRandomScoreValue()),
			Color::eColor::PURPLE,
			initialPosition,
			static_cast<char>(Direction::eDirection::STAY)),
		m_IsActive(false),
		m_ActivationChange(false)
	{};
	int GetScoreValue() const { return m_ScoreValue; } ;
	bool IsActive() const { return m_IsActive; };
	void ActivateFruit(Position position);
	void ActivateFruit(Position position, int value);
	void DeActivateFruit(Board& board);
	void SetActivationMode(bool actived);
	void SetActivationChangeFlag(bool activationChange) { m_ActivationChange = activationChange; };
	void SetScoreValue(int value) { m_ScoreValue = value; };
	int GetRandomScoreValue() { m_ScoreValue = 10 - (1 + (rand() % 5)); return m_ScoreValue; };
	char GetFruitFigure(int value) const;
	const bool& GetActivationChangeStatus() const { return m_ActivationChange; };
	void Erase(const int yCoord, const int xCoord, Board& board) const override;
};