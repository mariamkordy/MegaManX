
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
#include "MainMenu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>

using namespace sf;
using namespace std;

int main()
{
    // --- 1. WINDOW AND STATE INITIALIZATION ---
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");

    // Pass the window into the struct as a reference
    GameState condition(window);

    // Load assets immediately so textures aren't empty
    LoadAssets(condition);

    // --- 2. GAME OBJECTS AND ASSETS ---
    Player player;
    TileMap map;
    Background background;
    Foreground foreground;
    vector<Ground> grounds;
    vector<Wall> walls;
    vector<Checkpoint> checkpoints;
    View view;
    Clock clock;
    float deltaTime;
    DashSmoke dashsmoke[15];

    // Enemy and Trap Setup
    vector<Enemy> enemies;
    vector<FireTrap> fires;
    float groundY = 1880.0f;
    float fireDamageTimer = 0.0f;
    EneTextures eneTex;
    Texture fireTexture;

    // Loading Texture Assets
    fireTexture.loadFromFile("assets/textures/FIRE.png");
    eneTex.enemy1.loadFromFile("assets/textures/ENEMY1.png");
    eneTex.enemy2.loadFromFile("assets/textures/ENEMY2.png");
    eneTex.enemy3.loadFromFile("assets/textures/ENEMY3.png");
    eneTex.axe.loadFromFile("assets/textures/axe.png");
    eneTex.enemyBullet.loadFromFile("assets/textures/enemy_bullet.png");
    loadLevel(enemies, fires, eneTex);
    Start(player, view, window, grounds, walls, background, foreground, map);

    srand(time(0));
    setupPlayer(player);

    player.hitbox.setOrigin(20.f, 30.f);

    Vector2f lastCheckpointPos = player.sprite.getPosition();
    int healthAmount = 20;
    int maxHealth = 100;

    int lives = 3;
    bool gameOver = false;
    bool deadState = false;

    Clock deathClock;
    Clock gameOverClock;

    Texture heartTexture;

    if (!heartTexture.loadFromFile("assets/textures/heart.png"))
    {
        cout << "FAILED TO LOAD HEART TEXTURE\n";
    }


    Sprite hearts[3];
    for (int i = 0; i < 3; i++)
    {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.02f, 0.02f);
        hearts[i].setPosition(190.f + (i * 55.f), 30.f);
    }


    // Font setup for UI
    Font font;
    if (!font.loadFromFile("assets/fonts/MMRock9.ttf"))
        cout << "FONT FAILED" << endl;

    Text healthText;
    healthText.setFont(font);
    healthText.setCharacterSize(32);
    healthText.setFillColor(Color::White);
    healthText.setPosition(30, 100);

    Text statusText;
    statusText.setFont(font);
    statusText.setCharacterSize(40);
    statusText.setFillColor(Color::Red);
    statusText.setPosition(300, 280);

    // Initialize Projectiles
    playerBullets Bullets[10];
    for (int i = 0; i < 10; i++) {
        Bullets[i].active = false;
        Bullets[i].position = Vector2f(0.f, 0.f);
        Bullets[i].velocity = Vector2f(0.f, 0.f);
    }

    // Set Initial Position and Checkpoints
    //INITIALLY (100, 200)

    player.sprite.setPosition(100, 1000);
    lastCheckpointPos = player.sprite.getPosition();
    vector<Vector2f> checkpointPositions = {
        //{2593.49 , 1304},
        //{0 , 1600},
        {6300, 2870},
        {15686.8 , 420},
        //{18567.9 , 1434}
    };

    for (auto& pos : checkpointPositions)
        checkpoints.push_back(createCheckpoint(pos.x, pos.y));

    clock.restart();

    // healthbar function declaration
    void HEALTHBAR(RenderWindow & window, Player & player, Texture & texture);

    // --- 3. MAIN STATE LOOPS ---
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        switch (condition.menuIndex)
        {
        case 0: // --- MAIN MENU STATE ---
            window.setView(window.getDefaultView());
            MainMenu(condition);
            break;

        case 2: // --- CREDITS MENU STATE ---
            window.setView(window.getDefaultView());
            CreditsMenu(condition);
            break;

        case 3: // --- PAUSE MENU STATE ---
            window.setView(window.getDefaultView()); // Reset camera so menu isn't skewed
            PauseMenu(condition);
            break;

        case 1: // --- ACTIVE GAMEPLAY STATE ---
        default:
            // Process basic window events for the gameplay state

            if (condition.needsRestart) {
                // 1. Reset Player Stats and Position
                player.health = maxHealth;
                player.sprite.setPosition(100, 100);
                lastCheckpointPos = Vector2f(100, 100);

                lives = 3;
                gameOver = false;
                deadState = false;

                for (int i = 0; i < 3; i++)
                    hearts[i].setColor(Color::White);

              

                // 2. Clear out old enemies/traps and reload the level from scratch
                enemies.clear();
                fires.clear();
                loadLevel(enemies, fires, eneTex);

                // 3. Turn the flag off so it doesn't constantly reset every frame
                condition.needsRestart = false;
            }

            Event ev;
            while (window.pollEvent(ev))
            {
                if (ev.type == Event::Closed) window.close();
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) window.close();
                
                // --- NEW: PAUSE TRIGGER ---
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::P) {
                    condition.menuIndex = 3;          // Switch to Pause State
                    condition.pauseSelection = 0;     // Default to 'Resume'
                }
            }

            if (!deadState && !gameOver)
            {
                handleCheckpoints(player, checkpoints, lastCheckpointPos,
                    healthAmount, maxHealth, deltaTime);
                respawn(player, lastCheckpointPos);
            }

            if (player.health <= 0 && !deadState && !gameOver)
            {
                deadState = true;
                lives--;
                if (lives >= 0 && lives < 3)
                    hearts[lives].setColor(Color(255, 255, 255, 80));

                player.state = DYING;
                player.deathIndex = 0;
                player.runTimer = 0.f;
                player.velocity = Vector2f(0.f, 0.f);

                statusText.setString("YOU DIED");
                deathClock.restart();
            }
            if (deadState && !gameOver)
            {
                updateAnimation(player, deltaTime);

                // Wait for animation to finish (6 frames x 0.15s = ~0.9s)
                // then add a small pause before transitioning
                if (player.deathIndex >= 5 &&
                    deathClock.getElapsedTime().asSeconds() > 1.2f)
                {
                    deadState = false;

                    if (lives > 0)
                    {
                        // Respawn
                        player.health = maxHealth;
                        player.state = STANDING;
                        player.deathIndex = 0;
                        player.sprite.setPosition(lastCheckpointPos);

                        enemies.clear();
                        fires.clear();
                        loadLevel(enemies, fires, eneTex);

                        statusText.setString("");
                    }
                    else
                    {
                        // No lives left
                        gameOver = true;
                        statusText.setString("GAME OVER");
                        gameOverClock.restart();
                    }
                }
            }

            if (gameOver && gameOverClock.getElapsedTime().asSeconds() > 3.f)
            {
                lives = 3;
                gameOver = false;
                deadState = false;

                for (int i = 0; i < 3; i++)
                    hearts[i].setColor(Color::White);

                player.health = maxHealth;
                player.state = STANDING;
                player.deathIndex = 0;
                player.sprite.setPosition(100, 100);
                lastCheckpointPos = Vector2f(100, 100);
                enemies.clear();
                fires.clear();
                loadLevel(enemies, fires, eneTex);

                checkpoints.clear();
                for (auto& pos : checkpointPositions)
                    checkpoints.push_back(createCheckpoint(pos.x, pos.y));

                statusText.setString("");
                condition.menuIndex = 0; // back to main menu
            }

            if (!deadState && !gameOver)
            {
                playerMovement(player, deltaTime, dashsmoke, Bullets);
                updateAnimation(player, deltaTime);
                smokeupdate(player, dashsmoke, deltaTime);
                checkBulletEnemyCollision(Bullets, enemies);
                updatePlayerBullets(player, deltaTime, Bullets);
                playerPhysics(player, deltaTime);
                collision(player, grounds, walls);
                camera(player, view, window, background, foreground);
                updateEnemies(enemies, player, deltaTime);
                updateFires(fires, player, fireDamageTimer, deltaTime);
            }

            // UI Updates
            healthText.setString("HEALTH: " + to_string(player.health));

            // Rendering Gameplay Frame
            window.clear();
            Draw(player, window, grounds, walls, background, foreground, dashsmoke, Bullets, checkpoints, enemies, fires, eneTex, fireTexture);
            HEALTHBAR(window, player, player.healthbar);


            // Overlay Screen-Space Text HUD
            window.setView(window.getDefaultView());
            window.draw(healthText);
            window.draw(statusText);
            // Draw Hearts
            for (int i = 0; i < 3; i++)
                window.draw(hearts[i]);

            window.display();
            break;
        }
    } // End of while loop

    return 0;
}