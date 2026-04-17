#include "Collision.h"

void collision(Player& player, const sf::RectangleShape& ground)
{
    const float PLAYER_HEIGHT = 52.f;

    float playerBottom = player.sprite.getPosition().y + PLAYER_HEIGHT;
    float groundTop = ground.getGlobalBounds().top;

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