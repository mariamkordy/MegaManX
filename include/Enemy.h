#pragma once
#include <SFML/Graphics.hpp>
//FOR NOW, TO BE UPDATED LATER
struct Enemy {
    sf::Sprite sprite;
    sf::Vector2f position;
    int health = 100;
};