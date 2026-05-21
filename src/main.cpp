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
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

int main()
{
    // --- 1. WINDOW AND STATE INITIALIZATION ---
    VideoMode desktopMode = VideoMode::getDesktopMode();
    RenderWindow window(desktopMode, "Mega Man X");

    GameState condition(window);
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
    eneTex.fire = fireTexture; // Essential for Draw.cpp
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

    // --- AUDIO ---
    sf::SoundBuffer cpBuffer, shootBuffer, deathBuffer;
    if (!cpBuffer.loadFromFile("assets/sounds/checkpoints sound.wav")) cout << "Failed checkpoint sound!\n";
    if (!shootBuffer.loadFromFile("assets/sounds/shooting.wav")) cout << "Failed shoot sound!\n";
    if (!deathBuffer.loadFromFile("assets/sounds/death sound.wav")) cout << "Failed death sound!\n";

    sf::Sound cpSound(cpBuffer);
    sf::Sound shootSound(shootBuffer);
    sf::Sound deathSound(deathBuffer);
    shootSound.setVolume(100.f);

    // --- GAMEPLAY VARIABLES ---
    int maxHealth = 100;
    int healthAmount = 20;
    int lives = 3;
    bool deadState = false;
    bool gameOver = false;
    Clock deathClock;

    // Lives UI setup
    Texture heartTexture;
    if (!heartTexture.loadFromFile("assets/textures/heart.png")) cout << "FAILED TO LOAD HEART TEXTURE\n";
    Sprite hearts[3];
    for (int i = 0; i < 3; i++) {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.02f, 0.02f);
        hearts[i].setPosition(190.f + (i * 55.f), 30.f);
    }

    // --- INITIALIZE NEW GAME OVER MENU ---
    GameOverMenu gameOverMenu;
    gameOverMenu.init();

    // Font setup for UI
    Font font;
    if (!font.loadFromFile("assets/fonts/MMRock9.ttf")) cout << "FONT FAILED\n";

    Text healthText, statusText;
    healthText.setFont(font); healthText.setCharacterSize(32);
    healthText.setFillColor(Color::White); healthText.setPosition(30, 100);

    statusText.setFont(font); statusText.setCharacterSize(40);
    statusText.setFillColor(Color::Red); statusText.setPosition(300, 280);

    // Initialize Projectiles
    playerBullets Bullets[10];
    for (int i = 0; i < 10; i++) {
        Bullets[i].active = false; Bullets[i].position = Vector2f(0.f, 0.f); Bullets[i].velocity = Vector2f(0.f, 0.f);
    }

    // Checkpoints
    player.sprite.setPosition(100,100);
    Vector2f lastCheckpointPos = player.sprite.getPosition();
    vector<Vector2f> checkpointPositions = { {6300, 2870}, {15686.8,420} };
    for (auto& pos : checkpointPositions) checkpoints.push_back(createCheckpoint(pos.x, pos.y));

    clock.restart();
    void HEALTHBAR(RenderWindow & window, Player & player, Texture & texture);

    // --- 3. MAIN STATE LOOPS ---
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        switch (condition.menuIndex)
        {
        case 0: // MAIN MENU
            window.setView(window.getDefaultView());
            MainMenu(condition);
            break;

        case 2: // CREDITS MENU
            window.setView(window.getDefaultView());
            CreditsMenu(condition);
            break;

        case 3: // PAUSE MENU
            window.setView(window.getDefaultView());
            PauseMenu(condition);
            break;

        case 4: // --- INTERACTIVE GAME OVER MENU ---
            window.clear();
            gameOverMenu.updateAndDraw(window, condition);
            window.display();
            break;

        case 1: // ACTIVE GAMEPLAY
        default:
            // --- FULL RESTART LOGIC (From Menu) ---
            if (condition.needsRestart) {
                player.health = maxHealth;
                player.sprite.setPosition(100, 100);
                lastCheckpointPos = Vector2f(100, 100);
                lives = 3;
                deadState = false;
                gameOver = false;
                for (int i = 0; i < 3; i++) hearts[i].setColor(Color::White);

                enemies.clear(); fires.clear();
                loadLevel(enemies, fires, eneTex);
                gameOverMenu.stopMusic();
                condition.needsRestart = false;
            }

            Event ev;
            while (window.pollEvent(ev))
            {
                if (ev.type == Event::Closed) window.close();
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape) window.close();
                if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::P) {
                    condition.menuIndex = 3;
                    condition.pauseSelection = 0;
                }
            }

            // --- GAMEPLAY UPDATES ---
            if (!deadState && !gameOver) {
                handleCheckpoints(player, checkpoints, lastCheckpointPos, healthAmount, maxHealth, deltaTime, cpSound);
                respawn(player, lastCheckpointPos);
            }

            // --- DYING TRIGGER ---
            if (player.health <= 0 && !deadState && !gameOver) {
                deadState = true;
                lives--;
                if (lives >= 0 && lives < 3) hearts[lives].setColor(Color(255, 255, 255, 80));

                player.state = DYING;
                player.deathIndex = 0;
                player.runTimer = 0.f;
                player.velocity = Vector2f(0.f, 0.f);

                deathSound.play();
                statusText.setString("YOU DIED");
                deathClock.restart();
            }

            // --- DEATH ANIMATION FINISHED ---
            if (deadState && !gameOver) {
                updateAnimation(player, deltaTime);

                if (player.deathIndex >= 5 && deathClock.getElapsedTime().asSeconds() > 1.2f) {
                    deadState = false;

                    if (lives > 0) {
                        // Standard Respawn
                        deathSound.stop();
                        player.health = maxHealth;
                        player.state = STANDING;
                        player.deathIndex = 0;
                        player.sprite.setPosition(lastCheckpointPos);
                        //enemies.clear(); fires.clear();
                        //loadLevel(enemies, fires, eneTex);
                        statusText.setString("");
                    }
                    else {
                        // NO LIVES LEFT -> TRANSITION TO GAME OVER MENU (Case 4)
                        deathSound.stop();
                        gameOverMenu.inputDelayTimer.restart(); // Forces a 0.2s delay before reading new inputs
                        gameOverMenu.musicPlayed = false;       // Guarantees the music tracks reset and play
                        condition.menuIndex = 4;
                        statusText.setString("");
                    }
                }
            }

            // --- STANDARD PHYSICS & UPDATES ---
            if (!deadState && !gameOver) {
                playerMovement(player, deltaTime, dashsmoke, Bullets, shootSound, deathSound);
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

            // UI Text
            healthText.setString("HEALTH: " + to_string(player.health));

            // --- DRAW FRAME ---
            window.clear();

            // Draw Gameplay
            window.setView(view);
            Draw(player, window, grounds, walls, background, foreground, dashsmoke, Bullets, checkpoints, enemies, fires, eneTex, fireTexture);
            HEALTHBAR(window, player, player.healthbar);

            // Draw HUD
            window.setView(window.getDefaultView());
            window.draw(healthText);
            window.draw(statusText);
            for (int i = 0; i < 3; i++) {
                window.draw(hearts[i]);
            }

            window.display();
            break;
        }
    }

    return 0;
}