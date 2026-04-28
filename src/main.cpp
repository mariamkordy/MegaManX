#include "Player.h"
#include "Background.h"
#include "PlayerMovement.h"
#include "PlayerPhysics.h"
#include "UpdateAnimation.h"
#include "Collision.h"
#include "Camera.h"
#include "Draw.h"
#include "GameInit.h"
#include "TileMap.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


using namespace sf;
using namespace std;
int main()
{
    Player player;
    TileMap map;
    Background background;
    RectangleShape ground;
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");
    View view;

    Clock clock;
    float deltaTime;
    DashSmoke dashsmoke[15];

    bool jumpKeyReleased = true;

    Start(player, view, window, ground, background, map);

    while (window.isOpen())
    {
        window.clear();
        deltaTime = clock.restart().asSeconds();
        //CLOSING THE WINDOW
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed) {
                window.close();
            } 
            else if(ev.type == Event::KeyPressed) {
                if (ev.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        //drawTileMap(map, window);
        playerMovement(player, deltaTime, dashsmoke);
        updateAnimation(player, deltaTime, jumpKeyReleased);
        smokeupdate(player, dashsmoke, deltaTime);
        playerPhysics(player, deltaTime);
        collision(player, ground);
       
        camera(player, view, window, background);
        Draw(player, window, ground, background,dashsmoke);
       
    }

    return 0;
}