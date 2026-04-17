#include "GameInit.h"
#include <iostream>

void Start(Player& player, sf::View& view, sf::RenderWindow& window,
           sf::RectangleShape& ground, Background& background)
{
    player.facingRight = true;
    player.isRunning = false;
    player.isOnGround = false;
    player.animationLocked = false;

    if (!background.bgTexture.loadFromFile("assets/textures/bg.png"))
        std::cout << "BG FAILED\n";

    background.bgSprite.setTexture(background.bgTexture);
    background.bgSprite.setScale(2.5f, 2.5f);

    if (!player.jumpingAnimation.loadFromFile("assets/textures/jump.png"))
        std::cout << "JUMP FAILED\n";

    if (!player.runningAnimation.loadFromFile("assets/textures/running.png"))
        std::cout << "RUN FAILED\n";

    if (!player.standingAnimation.loadFromFile("assets/textures/standing.png"))
        std::cout << "STAND FAILED\n";

    player.sprite.setTexture(player.standingAnimation);
    player.sprite.setTextureRect(sf::IntRect(0, 0, 36, 52));
    player.sprite.setScale(3.f, 3.f);

    player.sprite.setPosition(100.f, 150.f);

    ground.setSize(sf::Vector2f(2000.f, 170.f));
    ground.setPosition(0.f, 900.f);

    view.setSize(1680.f, 1050.f);
    view.zoom(0.8f);

    window.setFramerateLimit(180);
}