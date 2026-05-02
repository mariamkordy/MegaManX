#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "UpdateAnimation.h"
#include "Background.h"
#include "Collision.h"
#include "Enemy.h"
#include "CheckPointSystem.h"

using namespace std;
void Draw(Player& player, sf::RenderWindow& window, const vector<Ground>& grounds, const vector<Wall>& walls, Background& background, Foreground& foreground, DashSmoke dashsmoke[100], playerBullets Bullets[10], vector<Checkpoint>& checkpoints, std::vector<Enemy>& enemies, std::vector<FireTrap>& fires,
    EneTextures& tex, sf::Texture& fireTex);


