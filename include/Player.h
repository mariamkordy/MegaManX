#pragma once

#include <SFML/Graphics.hpp>

struct Position
{
    float x;
    float y;
};

struct Player
{
    sf::CircleShape circle;
    Position position;
    sf::Vector2f velocity;
    int health;
    bool isGrounded;
};

// REQUIRED function declarations
void gravity(Player& player, float deltaTime);
void checkGround(Player& player, sf::RectangleShape& ground);
void player_movement(Player& player, float deltaTime);
void jump(Player& player);
void playerpos(Player& player);
void collision_with_frame(Player& player);