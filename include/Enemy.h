#pragma once
#include <SFML/Graphics.hpp>
//FOR NOW, TO BE UPDATED LATER

//struct Enemy {
//    sf::Sprite sprite;
//    sf::Vector2f position;
//    int health = 100;
//};
struct Enemy {
    sf::Vector2f pos;
    sf::Vector2f vel;
    int type = 1, health = 100, direction = 1;
    bool alive = true, grounded = false, dying = false;
    float speed = 100.f, startX = 0.f, patrolRange = 120.f, visionRange = 400.f;
    float shootTimer = 0.f;
    //Bullet bullets[MAX_BULLETS];
    float animTimer = 0.f;
    int animFrame = 0;
    bool isShooting = false;
    sf::Sprite sprite;//

    bool throwing = false, axeActive = false, axeReleased = false; //الفاس اترمي ولا لسه
    float axeTimer = 0.f;
    int axeFrame = 0;
    float throwCooldown = 0.f; // هيضرب تاني امتي
    sf::Vector2f axePos, axeDir; //موقع الفاس و اتجاهه
};

struct Bullet {
    sf::Vector2f pos;
    sf::Vector2f vel;
    int damage = 0;
    bool active = false;
    
};