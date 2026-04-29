#include "PlayerPhysics.h"
using namespace sf;
//APPLIES GRAVITY AND LOCKS PLAYER IN MAP
void playerPhysics(Player& player, float deltaTime)
{
    float gravity = 1500.f;

    player.sprite.move(player.velocity.x * deltaTime, 0);

    if (!player.isOnGround)
    {
        player.velocity.y += gravity * deltaTime;
        player.sprite.move(0, player.velocity.y * deltaTime);
    }

    const float worldWidth = 23176.2f;
    const float worldLeft = -10.1687f;

    FloatRect playerBounds = player.sprite.getGlobalBounds();
    Vector2f playerPos = player.sprite.getPosition();
    float playerCenterX = player.sprite.getPosition().x;

    if (playerCenterX > worldWidth)
        player.sprite.setPosition(worldWidth, playerPos.y);
    if (playerCenterX < worldLeft)
        player.sprite.setPosition(worldLeft, playerPos.y);

}