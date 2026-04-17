#include "UpdateAnimation.h"
#include <iostream>

void updateAnimation(Player& player, float deltaTime, bool& jumpKeyReleased)
{
    if (player.isOnGround)
    {
        player.animationLocked = false;
        player.jumpIndex = 0;
        player.jumpTimer = 0.f;
    }

    if (!player.isOnGround)
    {
        player.jumpTimer += deltaTime;
        player.animationLocked = true;
        player.isRunning = false;

        if (player.sprite.getTexture() != &player.jumpingAnimation)
            player.sprite.setTexture(player.jumpingAnimation);

        if (player.jumpTimer > 0.07f)
        {
            if (player.jumpIndex < 3)
                player.jumpIndex++;

            if (player.facingRight) {
                player.sprite.setTextureRect(sf::IntRect(player.jumpIndex * 29, 0, 29, 52));
            }
            else {
                player.sprite.setTextureRect(sf::IntRect(player.jumpIndex * 29 + 29, 0, -29, 52));
            }

            player.jumpTimer = 0.f;
        }
    }
    else if (player.isRunning && !player.animationLocked)
    {
        if (player.sprite.getTexture() != &player.runningAnimation)
            player.sprite.setTexture(player.runningAnimation);

        player.runTimer += deltaTime;

        int maxRunFrames = player.runningAnimation.getSize().x / 36;

        if (player.runTimer > 0.05f) {
            player.runIndex++;
            if (player.runIndex >= maxRunFrames)
                player.runIndex = 0;
            player.runTimer = 0.f;
        }

        if (player.facingRight) {
            player.sprite.setTextureRect(sf::IntRect(player.runIndex * 36, 0, 36, 52));
        }
        else {
            player.sprite.setTextureRect(sf::IntRect(player.runIndex * 36 + 36, 0, -36, 52));
        }
    }
    else if (!player.animationLocked)
    {
        if (player.sprite.getTexture() != &player.standingAnimation)
            player.sprite.setTexture(player.standingAnimation);

        if (!player.facingRight) {
            player.sprite.setTextureRect(sf::IntRect(36, 0, -36, 52));
        }
        else {
            player.sprite.setTextureRect(sf::IntRect(0, 0, 36, 52));
        }

        player.runIndex = 0;
    }
}