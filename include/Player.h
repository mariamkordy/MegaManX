#pragma once
#include <SFML/Graphics.hpp>

enum PlayerState {
    IDLE,
    RUN,
    JUMP
};

struct Player {
    sf::Sprite sprite;
    sf::RectangleShape hitbox;

    PlayerState state;

    int frameIndex=0;
    int health = 100;

    sf::Vector2f velocity;

    bool isOnGround = false;
    bool isStanding = false;
    bool isJumping = true;
    bool isRunning = false;
    bool facingRight = true;
    bool animationLocked = true;
    bool isDashing = false;

    // Animations
    sf::Texture runningAnimation;
    sf::Texture standingAnimation;
    sf::Texture jumpingAnimation;
    sf::Texture dashrunAnimation;
    sf::Texture smokeDashAnimation;

    int runIndex = 0;
    int jumpIndex = 0;
    
    int dashTimer = 0.f;
    float runTimer = 0.f;
    float jumpTimer = 0.f;
    float smokeTimer = 0.1f;

    const float dashduration = 0.5f;
};

struct DashSmoke {
    sf::Vector2f Position;  
    sf::Sprite display;
    bool visible = false;
    int smokeIndex = 0;
    float smokeDuration = 0.3;



};