#include "Camera.h"

#include <iostream>
using namespace sf;
using namespace std;
void camera(Player& player, sf::View& view, sf::RenderWindow& window, Background& background, Foreground& foreground)
{
    Vector2f playerPos = player.sprite.getPosition();
    FloatRect playerBounds = player.sprite.getGlobalBounds();
    float halfW = view.getSize().x / 2.f;
    float halfH = (view.getSize().y / 2.f);
    float playerCenterX = player.sprite.getPosition().x;
    float playerCenterY = player.sprite.getPosition().y;
    

    //--------------PREVENTS THE CAMERA FROM GOING OUTSIDE THE MAP--------------------
    const float worldWidth = 23286.2f;
    const float worldLeft = -10.1687f;
    const float worldHeight = 2200.f;
    
 
    //DO NOT PASS LEFT BORDER
    if (playerCenterX < worldLeft)
        playerCenterX = worldLeft;

    //STOP CAMERA BEFORE LEFT BORDER
    if (playerCenterX < halfW)
        playerCenterX = halfW;

    //STOP CAMERA BEFORE RIGHT BORDER
    if (playerCenterX > worldWidth - halfW)
        playerCenterX = worldWidth - halfW;

    //DO NOT PASS RIGHT BORDER
    if (playerCenterX > worldWidth)
        playerCenterX = worldWidth;

    if (playerCenterY < halfH)
        playerCenterY = halfH;
    //CLAMP TOP BORDER
    if (playerCenterY > worldHeight - halfH )
        playerCenterY = worldHeight - halfH;

    
    view.setCenter(playerCenterX, playerCenterY);
    window.setView(view);    

}