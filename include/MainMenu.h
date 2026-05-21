#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

struct GameState {
    sf::RenderWindow& window;
    sf::Event e;
    int menuIndex = 0;
    sf::Vector2f windowSize{ 1920.f, 1080.f };
    sf::Clock clock1;
    float deltaTime = 0.f;
    sf::View view;

    sf::SoundBuffer startBuffer;
    sf::Sound startSound;
    sf::SoundBuffer menuBuffer;
    sf::Sound menuSound;

    sf::Texture backgroundTex, creditsTex;
    sf::Sprite backgroundSprite, creditsSprite;
    sf::RectangleShape highlightBox;
    int currentSelection = 0;

    sf::Texture pauseTex;
    sf::Sprite pauseSprite;
    sf::RectangleShape pauseHighlightBox;
    sf::RectangleShape musicStatusBox;
    int pauseSelection = 0;
    bool isMusicOn = true;
    bool needsRestart = false;

    GameState(sf::RenderWindow& win) : window(win) {}
};

void LoadAssets(GameState& condition);
void MainMenu(GameState& condition);
void CreditsMenu(GameState& condition);
void PauseMenu(GameState& condition);

struct GameOverMenu {
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::CircleShape pointer;
    sf::Music gameOverMusic;
    bool musicPlayed = false;
    int selectedIndex = 0;
    sf::Clock inputDelayTimer;

    void init() {
        if (!backgroundTexture.loadFromFile("assets/textures/game_over2.png")) {
            std::cout << "FAILED TO LOAD GAME OVER BACKGROUND\n";
        }
        backgroundSprite.setTexture(backgroundTexture);

        if (!gameOverMusic.openFromFile("assets/sounds/game_over_music.mp3")) {
            std::cout << "FAILED TO LOAD GAME OVER MUSIC\n";
        }
        gameOverMusic.setLoop(false);

        pointer.setRadius(15.f);
        pointer.setFillColor(sf::Color::Red);
        pointer.setOrigin(15.f, 15.f);
    }

    void stopMusic() {
        gameOverMusic.stop();
        musicPlayed = false;
    }

    void handleInput(GameState& condition) {
        if (inputDelayTimer.getElapsedTime().asSeconds() < 0.2f) return;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            selectedIndex = 0;
            inputDelayTimer.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            selectedIndex = 1;
            inputDelayTimer.restart();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            inputDelayTimer.restart();
            if (selectedIndex == 0) {
                condition.needsRestart = true;
                condition.menuIndex = 1; // Gameplay
                stopMusic();
            }
            else if (selectedIndex == 1) {
                condition.needsRestart = true;
                condition.menuIndex = 0; // Return to Main Menu
                condition.currentSelection = 0; // <--- ADD THIS LINE HERE
                stopMusic();
            }
        }
    }

    void updateAndDraw(sf::RenderWindow& window, GameState& condition) {
        if (!musicPlayed) {
            gameOverMusic.play();
            musicPlayed = true;
        }

        handleInput(condition);

        window.setView(window.getDefaultView());
        sf::Vector2u windowSize = window.getSize();

        // Scale background
        sf::Vector2u texSize = backgroundTexture.getSize();
        backgroundSprite.setScale((float)windowSize.x / texSize.x, (float)windowSize.y / texSize.y);
        window.draw(backgroundSprite);

        // Positioning
        float centerX = windowSize.x / 2.0f;
        float newX = centerX - 300.f; // Shifted left

        if (selectedIndex == 0) {
            pointer.setPosition(newX, (windowSize.y * 0.6f) - 95.f);
        }
        else {
            pointer.setPosition(newX, (windowSize.y * 0.7f) - 110.f);
        }
        window.draw(pointer);
    }
};