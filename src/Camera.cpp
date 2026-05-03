#include "Camera.h"

#include <iostream>
using namespace sf;
using namespace std;

void camera(Player& player, View& view, RenderWindow& window, Background& background, Foreground& foreground)
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

    float worldTop;
    float worldBottom;

    // Determine bounds based on zone
    if (playerCenterX < 5656.f)
    {
        // Section 1
        worldTop = 1063.f;
        worldBottom = 1057.f + 256.f * 4.5f;
    }
    else if (playerCenterX < 11992.f)
    {
        // Section 2
        worldTop = 1057.f;
        worldBottom = 3369.f;
    }
    else if (playerCenterX < 15800.f)
    {
        // Section 3
        worldTop = -90.f;
        worldBottom = 3369.f;
    }
    else if (playerCenterX < 16322.f)
    {
        // Section 4
        worldTop = -104.f;
        worldBottom = 2216.f;
    }
    else
    {
        // Section 5
        worldTop = 1053.f;
        worldBottom = 2216.f;
    }

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

    //CLAMP TOP
    if (playerCenterY < worldTop + halfH)
        playerCenterY = worldTop + halfH;

    //CLAMP BOTTOM
    if (playerCenterY > worldBottom - halfH)
        playerCenterY = worldBottom - halfH;

    view.setCenter(playerCenterX, playerCenterY);
    window.setView(view);
}