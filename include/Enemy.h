
#ifndef ENE_H
#define ENE_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Player.h"

//---------Constant Number For Animation----------------
const int MAX_BULLETS = 5;
const float ENEMY_W = 172, ENEMY_H = 188;
const float ENEMY3_W = 138, ENEMY3_H = 150;
const int AXE_W = 160, AXE_H = 200;
const int FIRE_W = 29, FIRE_H = 29, FIRE_FRAMES = 11;
const float ENEMY_SCALE = 0.9f, ENEMY3_SCALE = 1.f, AXE_SCALE = 0.7f;

struct Bullet {
    sf::Vector2f pos;
    sf::Vector2f vel;
    int damage = 0;
    bool active = false;
};

struct Enemy {
    sf::Vector2f pos;
    sf::Vector2f vel;
    int type = 1, health = 100, direction = 1;
    bool alive = true, grounded = false, dying = false;
    float speed = 150.f, startX = 0.f, patrolRange = 120.f, visionRange = 400.f;
    float shootTimer = 0.f;
    Bullet bullets[MAX_BULLETS];
    float animTimer = 0.f;
    int animFrame = 0;
    bool isShooting = false;
    sf::Sprite sprite;
    sf::Sprite axeSprite;
    bool throwing = false, axeActive = false, axeReleased = false; //الفاس اترمي ولا لسه
    float axeTimer = 0.f;
    int axeFrame = 0;
    float throwCooldown = 0.f; // هيضرب تاني امتي
    sf::Vector2f axePos, axeDir; //موقع الفاس و اتجاهه
};

struct FireTrap {
    sf::Vector2f start;
    sf::Vector2f drop;
    int frame = 1;
    float scale = -1.6f, fallSpeed = 120.f, fallDistance = 350.f, startGap = 18.f;
    //عشان نضبط البدايه و السقوط بتاع النار
    FireTrap(float x, float y) : start(x, y), drop(x, y + 18.f) {}
    sf::Sprite sprite;
};

struct EneTextures {
    sf::Texture enemy1, enemy2, enemy3, axe, fire;
};
inline float getDist(sf::Vector2f a, sf::Vector2f b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float sum = (dx * dx) + (dy * dy);
    return std::sqrt(sum);
}

void loadLevel(std::vector<Enemy>& enemies, std::vector<FireTrap>& fires, EneTextures& eneTex);
void updateEnemies(std::vector<Enemy>& enemies, Player& player, float groundY, float dt);
void updateFires(std::vector<FireTrap>& fires, Player& player, float& fireDamageTimer, float dt);
void drawEnemies(sf::RenderWindow& window, std::vector<Enemy>& enemies, EneTextures& tex, sf::Vector2f playerPos);
void drawFires(sf::RenderWindow& window, std::vector<FireTrap>& fires, sf::Texture& tex);

#endif