#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Collision.h"
#include "TileMap.h"

using namespace sf;
void Start(Player& player, View& view, RenderWindow& window,
    std::vector<Ground>& grounds , Background& background, Foreground& foreground, TileMap& map);