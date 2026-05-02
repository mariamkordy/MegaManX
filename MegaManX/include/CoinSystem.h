#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//TO BE UPDATED
struct Coin {
    sf::CircleShape shape;
    bool collected = false;
};

void checkCoinCollection(std::vector<Coin>& coins, sf::FloatRect playerBounds, int& balance);