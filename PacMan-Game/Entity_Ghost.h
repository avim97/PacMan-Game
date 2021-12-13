#pragma once
#include "Entity.h"

class Entity_Ghost : Public Entity {
Public:
	Entity_Ghost(const int x, const int y, Color::eColor color) : Entity(static_cast<int>(BoardObjects::GHOST), color, { x, y }, static_cast<char>(Direction::eDirection::STAY)) {};
	override void Move(char nextDir);
Private:

};