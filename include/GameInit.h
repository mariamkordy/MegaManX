#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Collision.h"
#include "TileMap.h"

using namespace sf;
using namespace std;
void Start(Player& player, View& view, RenderWindow& window,
    vector<Ground>& grounds, vector<Wall>& walls, Background& background, Foreground& foreground, TileMap& map);