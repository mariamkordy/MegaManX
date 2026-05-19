<<<<<<< HEAD
﻿#include "Player.h"
=======
﻿



#include "Player.h"
>>>>>>> df15468d966cc9448b7ea716db38c108ae1c9fc7
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

    loadLevel(enemies, fires, eneTex);
    Start(player, view, window, grounds, walls, background, foreground, map);

    srand(time(0));
    setupPlayer(player);

    player.hitbox.setOrigin(20.f, 30.f);

    Vector2f lastCheckpointPos = player.sprite.getPosition();
    int healthAmount = 20;
    int maxHealth = 100;

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
    player.sprite.setPosition(100, 100);
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

            // CHECKPOINT LOGIC
            handleCheckpoints(player, checkpoints, lastCheckpointPos, healthAmount, maxHealth, deltaTime);
            respawn(player, lastCheckpointPos);

            // UI Updates
            healthText.setString("HEALTH: " + to_string(player.health));
            if (player.health <= 0) statusText.setString("YOU DIED");
            else if (Keyboard::isKeyPressed(Keyboard::R)) statusText.setString("RESPAWNING");
            else statusText.setString("");

            // Gameplay Engine Logic Updates
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

            // Rendering Gameplay Frame
            window.clear();

            Draw(player, window, grounds, walls, background, foreground, dashsmoke, Bullets, checkpoints, enemies, fires, eneTex, fireTexture);
            HEALTHBAR(window, player, player.healthbar);

            // Overlay Screen-Space Text HUD
            window.setView(window.getDefaultView());
            window.draw(healthText);
            window.draw(statusText);
            window.display();
            break;
        }
    } // End of while loop

    return 0;
}