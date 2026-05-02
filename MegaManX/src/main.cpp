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
#include "Enemy.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>


using namespace sf;
using namespace std;

sf::Vector2f norm(sf::Vector2f v);
void loadLevel(std::vector<Enemy>& enemies, std::vector<FireTrap>& fires);
void updateEnemies(std::vector<Enemy>& enemies, sf::Vector2f playerPos, float& playerHealth, float groundY, float dt);
void updateFires(std::vector<FireTrap>& fires, sf::Vector2f playerPos, float& playerHealth, float& fireDamageTimer, float dt);
float getDist(sf::Vector2f p1, sf::Vector2f p2); // دالة المسافة مهمة جداً


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

    //ENEMIES
    vector<Enemy> enemies;       // وعاء الأعداء
    vector<FireTrap> fires;      // وعاء فخاخ النار
    float groundY = 3000.0f;      // مستوى الأرض (عدلي الرقم حسب خريطتك)
    float fireDamageTimer = 0.0f; // تايمر ضرر النار
    float playerHealth = 100.0f;
    EneTextures eneTex;
    Texture fireTexture;
    fireTexture.loadFromFile("assets/textures/FIRE.png");
    eneTex.enemy1.loadFromFile("assets/textures/ENEMY1.png");
    eneTex.enemy2.loadFromFile("assets/textures/ENEMY2.png");
    eneTex.enemy3.loadFromFile("assets/textures/ENEMY3.png");
    eneTex.axe.loadFromFile("assets/textures/axe.png");  

    loadLevel(enemies, fires);
    Start(player, view, window, grounds, walls, background, foreground, map);

    while (window.isOpen())
    {

        cout << "Player Position: " << player.sprite.getPosition().x <<"," << player.sprite.getPosition().y << endl;
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
        playerMovement(player, deltaTime, dashsmoke);
        //PLAYER ANIMATIONS
        updateAnimation(player, deltaTime);
        //ALSO PLAYER ANIMATION
        smokeupdate(player, dashsmoke, deltaTime);
        //GRAVITY AND KEEPING THE PLAYER INSIDE MAP BOUNDS
        playerPhysics(player, deltaTime);
        //COLLISION
        collision(player, grounds, walls);
        //CAMERA + LOCKS VIEW INSIDE MAP BOUNDS
        camera(player, view, window, background, foreground);
        //DRAWS SPRITES


        sf::Vector2f pPos = player.sprite.getPosition();
        updateEnemies(enemies, pPos, playerHealth, groundY, deltaTime);

        updateFires(fires, pPos, playerHealth, fireDamageTimer, deltaTime);  

        //DRAWS SPRITES
        // السطر المتعدل في الماين     
        Draw(player, window, grounds, walls, background, foreground, dashsmoke, enemies, fires, eneTex, fireTexture);
       
    }

    return 0;
}