#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

void playerMovement(Player& player, bool jumpKeyReleased,float deltaTime,DashSmoke dashsmoke[100]);