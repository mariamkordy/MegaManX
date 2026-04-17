#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"

void Start(Player& player, sf::View& view, sf::RenderWindow& window,
           sf::RectangleShape& ground, Background& background);