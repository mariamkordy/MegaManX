#include "Collision.h"

#include <iostream>
using namespace sf;
using namespace std;

void collision(Player& player, const vector<Ground>& grounds, const vector<Wall>& walls)
{
    player.isOnGround = false;
    player.isOnWall = false;
    const float PLAYER_HEIGHT = 56.f;
    const float PLAYER_WIDTH = 66.f;

    float playerLeft = player.sprite.getPosition().x;
    float playerRight = playerLeft + PLAYER_WIDTH;
    float playerBottom = player.sprite.getPosition().y + PLAYER_HEIGHT;
    float playerTop = player.sprite.getPosition().y;

    for (const auto& ground : grounds) {
        FloatRect groundBounds = ground.rectangle.getGlobalBounds();

        float groundLeft = groundBounds.left;
        float groundRight = groundBounds.left + groundBounds.width;
        float groundTop = groundBounds.top;

        bool overlapsGX = playerRight > groundLeft && playerLeft < groundRight;
        bool overlapsGY = playerBottom > groundBounds.top && playerTop < groundBounds.top + groundBounds.height;

        // Player hit the block from below — push them down
        if (overlapsGX && overlapsGY && player.velocity.y < 0) {
            player.sprite.setPosition(player.sprite.getPosition().x, groundBounds.top + groundBounds.height);
        }
        // Player landed on top — only if player is above the ground block
        else if (overlapsGX && playerBottom >= groundTop && playerTop <= groundTop && player.velocity.y >= 0) {
            player.sprite.setPosition(player.sprite.getPosition().x, groundTop - PLAYER_HEIGHT);
            player.velocity.y = 0;
            player.isOnGround = true;
        }
    }
    

    for (const auto& wall : walls) {
        FloatRect wallBounds = wall.rectangle.getGlobalBounds();
        float wallLeft = wallBounds.left;
        float wallRight = wallBounds.left + wallBounds.width;
        float wallTop = wallBounds.top;

        bool overlapsWX = playerRight > wallLeft && playerLeft < wallRight;

        // IF THE PLAYER APPROACHES A WALL BLOCK FROM BELOW, IGNORE IT
        if (overlapsWX && player.sprite.getPosition().y > wallBounds.top + wallBounds.height) {
            continue;
        }

        if (overlapsWX) {
            float moveRight = wallLeft - playerRight;
            float moveLeft = wallRight - playerLeft;
            if (player.sprite.getPosition().y <= wallTop) {
                continue;
            }
            if (abs(moveRight) > abs(moveLeft)) {
                player.sprite.setPosition(wallRight, player.sprite.getPosition().y);
                player.isOnWall = true;
            }
            else if (abs(moveRight) < abs(moveLeft)) {
                player.sprite.setPosition(wallLeft - PLAYER_WIDTH, player.sprite.getPosition().y);
                player.isOnWall = true;
            }
        }
    }
}