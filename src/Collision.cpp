#include "Collision.h"

#include <iostream>
using namespace sf;
using namespace std;
//HANDLES COLLISION WITH THE GROUND
void collision(Player& player, const std::vector<Ground>& grounds)
{
    player.isOnGround = false;
    const float PLAYER_HEIGHT = 56.f;
    const float PLAYER_WIDTH = 36.f;
    for (const auto& ground : grounds) {
        FloatRect groundBounds = ground.rectangle.getGlobalBounds();

        float playerLeft = player.sprite.getPosition().x;
        float playerRight = playerLeft + PLAYER_WIDTH;
        float playerBottom = player.sprite.getPosition().y + PLAYER_HEIGHT;

        float groundLeft = groundBounds.left;
        float groundRight = groundBounds.left + groundBounds.width;
        float groundTop = groundBounds.top;

        bool overlapsX = playerRight > groundLeft && playerLeft < groundRight;
        //IF THE PLAYER APPROACHES A GROUND BLOCK FROM BELOW, IGNORE IT 
        if (overlapsX && player.sprite.getPosition().y > groundBounds.top + groundBounds.height) {
            continue;
        }
        //IF THE PLAYER APPROACHES A GROUND BLOCK FROM ABOVE, PLACE IT ON THE BLOCK
        else if (overlapsX && playerBottom >= groundTop && player.velocity.y >= 0)
        {
            player.sprite.setPosition(
                player.sprite.getPosition().x,
                groundTop - PLAYER_HEIGHT
            );
            player.velocity.y = 0;
            player.isOnGround = true;
        }
        
       
    }
}