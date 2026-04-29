#include "Camera.h"

#include <iostream>
using namespace sf;
using namespace std;
void camera(Player& player, sf::View& view, sf::RenderWindow& window, Background& background, Foreground& foreground)
{
    Vector2f playerPos = player.sprite.getPosition();
    FloatRect playerBounds = player.sprite.getGlobalBounds();
    float fixedY = view.getSize().y / 2.f;
    float halfW = view.getSize().x / 2.f;
    float playerCenterX = player.sprite.getPosition().x;


    //PREVENTS THE CAMERA FROM GOING OUTSIDE THE MAP
    const float worldWidth = 23286.2f;
    const float worldLeft = -10.1687f;
    if (playerCenterX < worldLeft)
        playerCenterX = worldLeft;
    if (playerCenterX < halfW)
        playerCenterX = halfW;
    if (playerCenterX > worldWidth - halfW)
        playerCenterX = worldWidth - halfW;
    if (playerCenterX > worldWidth)
        playerCenterX = worldWidth;
    view.setCenter(playerCenterX, playerPos.y);
    window.setView(view);    

}