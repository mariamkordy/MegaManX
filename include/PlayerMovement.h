#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"

void playerMovement(Player& player, float deltaTime,DashSmoke dashsmoke[100],playerBullets Bullets[10], sf::Sound& shootSound, sf::Sound& deathSound);