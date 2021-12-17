#pragma once
#include "GameCreature.h"



class Pacman : public GameCreature {
private:
	int m_life;
	int m_score;
public:
	Pacman() : 
		GameCreature(
			static_cast<int>(BoardObjects::PACMAN),
			Color::eColor::YELLOW,
			{ 36, 14 },
			static_cast<char>(Direction::eDirection::STAY)),
		m_life(3),
		m_score(0)
	{};
	int GetCurrentLives() const { return m_life; };
	void UpdateLife();
	int GetCurrentScore() const { return m_score; };
	bool UpdateScore(Board& board);
	bool IsAlive() const;
	virtual void Erase(const int yCoord, const int xCoord, Board& board) const override;


};

