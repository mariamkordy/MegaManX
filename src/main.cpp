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
    Foreground foreground;
    vector <Ground> grounds;
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");
    View view;

    Clock clock;
    float deltaTime;
    DashSmoke dashsmoke[15];

    
    Start(player, view, window, grounds, background, foreground, map);

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
        sf::Vector2i position = sf::Mouse::getPosition(window);
        //std::cout << "Mouse X: " << position.x << ", Y: " << position.y << std::endl;
        //ANY MOVEMENT THAT DEPENDS ON USER INPUT
        playerMovement(player, deltaTime, dashsmoke);
        //PLAYER ANIMATIONS
        updateAnimation(player, deltaTime);
        //ALSO PLAYER ANIMATION
        smokeupdate(player, dashsmoke, deltaTime);
        //GRAVITY AND KEEPING THE PLAYER INSIDE MAP BOUNDS
        playerPhysics(player, deltaTime);
        //COLLISION
        collision(player, grounds);
        //CAMERA + LOCKS VIEW INSIDE MAP BOUNDS
        camera(player, view, window, background, foreground);
        //DRAWS SPRITES
        Draw(player, window, grounds, background, foreground, dashsmoke);
       
    }

    return 0;
}