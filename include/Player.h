#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

//When printed in the terminal, only the corresponding numbers are displayed, not strings.
enum PlayerState {
    STANDING, //0
    RUNNING, //1
    JUMPING, //2
    DASHING, //3
    ONWALL,
    TELEPORT,
    JUMPSHOOTING,
    RUNSHOOTING,
    IDLESHO,
    DASHSHOOTING,
    HURT, 
    DEAD  

};

struct Player {
    Sprite sprite;
    RectangleShape hitbox;
    PlayerState state;
    int health = 100;

    Texture texture;
    float speed;
    int frame;
    float animationTimer;
    float animationSpeed;

    Vector2f velocity;

    bool isOnGround = false;
    bool facingRight = true;
    bool isDashing = false;
    bool isOnWall = false;
   //shooting part
    bool isteleporting = true;
    bool ishooting = false;
    bool isjumpsh = false;
    bool isdashshooting = false;
    ////////////////
    
    // Animations (TEXTURES + VARIABLES)
    Texture runningAnimation;
    Texture standingAnimation;
    Texture jumpingAnimation;
    Texture dashrunAnimation;
    Texture smokeDashAnimation;    
    Texture playerBulletAnimation;

    //player shooting
    Texture shootingwhilerunning;
    Texture jump;
    Texture teleport;

    Texture  dashshooting;
    Texture idlesho;

    //Texture dashshooting;


    //////////

    int runIndex = 0;
    int jumpIndex = 0;
    //player shooting 
    int shootingindex = 0;
    int jumpshootingindex = 0;
    /////////////////
    
    float dashTimer = 0.f;
    float runTimer = 0.f;
    float jumpTimer = 0.f;
    float smokeTimer = 0.f;
    int smokenumber = 15;
    float shootingTimer = 0.f;
    float bulletDamage = 10.f;
    bool isAlive = true;
    
    const float dashduration = 0.05f;

    const int noOfBullets = 10;
};

struct DashSmoke {
    Vector2f Position;  
    Sprite display;
    bool visible = false;
    int smokeIndex = 0;
    float smokeDuration = 0.3f;
};

struct playerBullets {
    Vector2f position;
    Vector2f velocity;
    Sprite display;
    bool active;
};