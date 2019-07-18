#pragma once
#include "project.h"
#include "GameState.h"
#include "Game/Game.h"

void changeState(GameState*& current_state, State& next_state, sf::RenderWindow& window);
