#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "TileMap.h"

using namespace sf;
void Start(Player& player, View& view, RenderWindow& window,
           RectangleShape& ground, Background& background, TileMap& map);