#pragma once
#include "Entity.h"

class Entity_Pacman : public Entity {

public:
	Entity_Pacman() : Entity(static_cast<int>(BoardObjects::PACMAN), Color::eColor::YELLOW, { 36, 14 }, static_cast<char>(Direction::eDirection::STAY)) {};
	void Move (char nextDir);
};

