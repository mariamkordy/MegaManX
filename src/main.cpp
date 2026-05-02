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
#include "Combat.h"
#include "Enemy.h"

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
    vector <Wall> walls;
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");
    //Style::Fullscreen
    View view;

    Clock clock;
    float deltaTime;
    DashSmoke dashsmoke[15];
    playerBullets Bullets[10];
    for (int i = 0; i < 10; i++) {
        Bullets[i].active = false;
    }
    Enemy enemies[10];
    int enemyCount=10;
    
    Start(player, view, window, grounds, walls, background, foreground, map);

    while (window.isOpen())
    {

        cout << player.state<<endl;
       
        //cout << "Player Position: " << player.sprite.getPosition().x <<"," << player.sprite.getPosition().y << endl;
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
        //ANY MOVEMENT THAT DEPENDS ON USER INPUT
        playerMovement(player, deltaTime, dashsmoke, Bullets);
        //PLAYER ANIMATIONS
        updateAnimation(player, deltaTime);
        //ALSO PLAYER ANIMATION
        smokeupdate(player, dashsmoke, deltaTime);
        //combat(player killing enemies)
        checkBulletEnemyCollision(Bullets, enemies, enemyCount);
        //player bullets 
        updatePlayerBullets(player, deltaTime, Bullets);
        //GRAVITY AND KEEPING THE PLAYER INSIDE MAP BOUNDS
        playerPhysics(player, deltaTime);
        //COLLISION
        collision(player, grounds, walls);
        //CAMERA + LOCKS VIEW INSIDE MAP BOUNDS
        camera(player, view, window, background, foreground);
        //DRAWS SPRITES
        Draw(player, window, grounds,walls, background, foreground, dashsmoke,Bullets);
       
    }

    return 0;
}