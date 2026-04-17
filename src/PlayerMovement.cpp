#include "PlayerMovement.h"
#include <SFML/Window/Keyboard.hpp>

void playerMovement(Player& player, bool jumpKeyReleased)
{
    float speed = 300.f;

    player.isRunning = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.isOnGround)
    {
        player.velocity.y = -850.f;
        player.isOnGround = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.velocity.x = -speed;
        player.isRunning = true;
        player.facingRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.velocity.x = speed;
        player.isRunning = true;
        player.facingRight = true;
    }
    else {
        player.velocity.x = 0.f;
    }
}