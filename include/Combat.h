#pragma once
#include <SFML/Graphics.hpp>

//FOR NOW, TO BE UPDATED
struct Bullet {
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

void updateBullets(std::vector<Bullet>& bullets, float deltaTime);