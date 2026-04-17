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

    int frameIndex = 0;
    int health = 100;

    sf::Vector2f velocity;

    bool isOnGround = false;
    bool isStanding = false;
    bool isJumping = true;
    bool isRunning = false;
    bool facingRight = true;
    bool animationLocked = false;

    // Animations
    sf::Texture runningAnimation;
    sf::Texture standingAnimation;
    sf::Texture jumpingAnimation;

    int runIndex = 0;
    int jumpIndex = 0;

    float runTimer = 0.f;
    float jumpTimer = 0.f;
};