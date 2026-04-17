#include "PlayerPhysics.h"


void playerPhysics(Player& player, float deltaTime)
{
    float gravity = 1500.f;

    player.sprite.move(player.velocity.x * deltaTime, 0);

    if (!player.isOnGround)
    {
        player.velocity.y += gravity * deltaTime;
        player.sprite.move(0, player.velocity.y * deltaTime);
    }
}