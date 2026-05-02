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
#include "CheckPointSystem.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include<ctime>
#include<string>
#include<vector>
#include<cstdlib>


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
    vector<Checkpoint> checkpoints;
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");
    //Style::Fullscreen
    View view;

    Clock clock;
    float deltaTime;
    DashSmoke dashsmoke[15];

    srand(time(0));
    setupPlayer(player);
    
    
    Vector2f lastCheckpointPos = player.sprite.getPosition();
    int healthAmount = 20;
    int maxHealth = 100;

    // Font + health text
    Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) 
        return -1;

    Text healthText;
    healthText.setFont(font);
    healthText.setCharacterSize(20);
    healthText.setFillColor(Color::White);
    healthText.setPosition(10, 10);


    //STATUS TEXT(SHOWS IF DEAED OR RESPAWN MESSAGE)
    Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(40);
    statusText.setFillColor(Color::Red);
    statusText.setPosition(300, 280);
    
    playerBullets Bullets[10];
    for (int i = 0; i < 10; i++) {
        Bullets[i].active = false;
    }
    Enemy enemies[10];
    int enemyCount=10;
    
    Start(player, view, window, grounds, walls, background, foreground, map);

    vector<Vector2f> checkpointPositions = {
            {1400.f,  1550.f},
            {1900.f,  1550.f},
            {2500.f, 1350.f},
            {3000.f, 1450.f},
            {6000.f, 1300.f},
            {5700.f, 1450.f},
            {3900.f, 1400.f},
            {2300.f, 1450.f},
            {1800.f, 1350.f},
            {5500.f, 1450.f},
    };

    for (auto& pos : checkpointPositions)
        checkpoints.push_back(createCheckpoint(pos.x, pos.y));


    while (window.isOpen())
    {

        cout << player.state<<endl;
       
        //cout << "Player Position: " << player.sprite.getPosition().x <<"," << player.sprite.getPosition().y << endl;
        window.clear();
        deltaTime = clock.restart().asSeconds();
        if (player.isOnWall == true)
        cout << "PLAYER ON WALL" << endl;
        
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

        // CHECKPOINT LOGIC
        handleCheckpoints(player, checkpoints, lastCheckpointPos, healthAmount, maxHealth);
        respawn(player, lastCheckpointPos);
        

        healthText.setString("HEALTH: " + to_string(player.health));

        if (player.health <= 0)
        {
            statusText.setString("YOU DIED");
        }
        else if (Keyboard::isKeyPressed(Keyboard::R))
        {
            statusText.setString("RESPAWNING");
        }
        else
        {
            statusText.setString("");
        }


        window.clear();

        //DRAWS SPRITES
        Draw(player, window, grounds,walls, background, foreground, dashsmoke, Bullets, checkpoints);

        window.setView(window.getDefaultView());
        window.draw(healthText);
        window.draw(statusText);
        window.display();
    }

    return 0;
}