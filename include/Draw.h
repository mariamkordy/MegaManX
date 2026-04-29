#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Background.h"
#include "Collision.h"
using namespace std;

void Draw(Player& player, sf::RenderWindow& window,
    const vector<Ground>& grounds, Background& background, Foreground& foreground,DashSmoke dashsmoke[100]);