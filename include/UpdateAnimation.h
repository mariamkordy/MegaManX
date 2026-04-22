#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

void updateAnimation(Player& player, float deltaTime, bool& jumpKeyReleased);
void smokeupdate(Player& player, DashSmoke dashsmoke[15], float deltaTime);