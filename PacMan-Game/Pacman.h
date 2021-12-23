#pragma once
#include "GameCreature.h"



class Pacman : public GameCreature {
private:
	int m_Lives;
	int m_BreadcrumbsScore;
	int m_FruitScore;
	Legend m_Legend;
public:
	Pacman(const Position& initialPosition) : 
		GameCreature(
			static_cast<int>(BoardObjects::PACMAN),
			Color::eColor::YELLOW,
			initialPosition,
			static_cast<char>(Direction::eDirection::STAY)),
		m_Lives(3),
		m_BreadcrumbsScore(0),
		m_FruitScore(0)
	{};
	int GetCurrentLives() const { return m_Lives; };
	void UpdateLife();
	void UpdateLife(int lives);
	int GetBreadcrumbScore() const { return m_BreadcrumbsScore; };
	bool UpdateBreadcrumbScore(Board& board);
	void UpdateFruitScore(int score) { m_FruitScore += score; };
	bool IsAlive() const;
	virtual void Erase(const int yCoord, const int xCoord, Board& board) const override;
	int GetFruitScore() { return m_FruitScore; };

};

