#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.h"
#include "UpdateAnimation.h"
#include "Background.h"
#include "Collision.h"
#include "Enemy.h"


using namespace std;


void Draw(
    Player& player, 
    sf::RenderWindow& window, 
    std::vector<Ground>& grounds,
    std::vector<Wall>& walls, 
    Background& background, 
    Foreground& foreground,
    DashSmoke dashsmoke[], 
    std::vector<Enemy>& enemies, 
    std::vector<FireTrap>& fires,
    EneTextures& eneTex, 
    sf::Texture& fireTexture
);