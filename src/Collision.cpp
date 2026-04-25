#include "Collision.h"

using namespace sf;

void collision(Player& player, const RectangleShape& ground)
{
    const float PLAYER_HEIGHT = 56.f;
    const float PLAYER_WIDTH = 36.f;

    float playerBottom = player.sprite.getPosition().y + PLAYER_HEIGHT;
    float groundTop = ground.getGlobalBounds().top;
    float playerX = player.sprite.getPosition().x + PLAYER_WIDTH;
    float groundTerminal;

    if (playerBottom >= groundTop && player.velocity.y >= 0)
    {
        player.sprite.setPosition(
            player.sprite.getPosition().x,
            groundTop - PLAYER_HEIGHT
        );

        player.velocity.y = 0;
        player.isOnGround = true;
    }
    else {
        player.isOnGround = false;
    }
}