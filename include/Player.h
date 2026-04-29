#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//When printed in the terminal, only the corresponding numbers are displayed, not strings.
enum PlayerState {
    STANDING, //0
    RUNNING, //1
    JUMPING, //2
    DASHING //3
};

struct Player {
    Sprite sprite;
    RectangleShape hitbox;
    PlayerState state;
    int health = 100;

    Vector2f velocity;

    bool isOnGround = false;
    bool facingRight = true;
    bool isDashing = false;

    // Animations (TEXTURES + VARIABLES)
    Texture runningAnimation;
    Texture standingAnimation;
    Texture jumpingAnimation;
    Texture dashrunAnimation;
    Texture smokeDashAnimation;

    int runIndex = 0;
    int jumpIndex = 0;
    
    float dashTimer = 0.f;
    float runTimer = 0.f;
    float jumpTimer = 0.f;
    float smokeTimer = 0.f;
    int smokenumber = 15;

    const float dashduration = 0.05f;
};

struct DashSmoke {
    Vector2f Position;  
    Sprite display;
    bool visible = false;
    int smokeIndex = 0;
    float smokeDuration = 0.3f;
};