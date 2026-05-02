#pragma once
#include <SFML/Graphics.hpp>
#include "player.h"//
#include "Enemy.h"//
#include <vector>

//FOR NOW, TO BE UPDATED
//struct Bullet {
//    sf::CircleShape shape;
//    sf::Vector2f velocity;
//};

//struct playerBullets {
//    sf::Vector2f position;
//    sf::Vector2f velocity;
//    sf::Sprite display;
//    bool active;
//};

void updateBullets(std::vector<Bullet>& bullets, float deltaTime);
void checkBulletEnemyCollision(playerBullets Bullets[10], std::vector<Enemy>&enemies);