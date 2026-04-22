#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"

void Draw(Player& player, sf::RenderWindow& window,
    sf::RectangleShape& ground, Background& background,DashSmoke dashsmoke[100]);