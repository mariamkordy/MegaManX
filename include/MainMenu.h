

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>

struct GameState {
    sf::RenderWindow& window;
    sf::Event e;

    // State Control
    // 0 = Main Menu, 1 = Gameplay, 2 = Credits, 3 = Pause Menu
    int menuIndex = 0;
    sf::Vector2f windowSize{ 1920.f, 1080.f };
    sf::Clock clock1;
    float deltaTime = 0.f;
    sf::View view;

    //Audio
    sf::SoundBuffer startBuffer;
    sf::Sound startSound;

    sf::SoundBuffer menuBuffer;
    sf::Sound menuSound;

    // Main Menu Assets
    sf::Texture backgroundTex, creditsTex;
    sf::Sprite backgroundSprite, creditsSprite;
    sf::RectangleShape highlightBox;
    int currentSelection = 0;

    // --- NEW PAUSE MENU ASSETS ---
    sf::Texture pauseTex;
    sf::Sprite pauseSprite;
    sf::RectangleShape pauseHighlightBox;   // Highlights Resume/Music/Return
    sf::RectangleShape musicStatusBox;      // Highlights 'ON' or 'OFF' specifically
    int pauseSelection = 0;                 // 0 = Resume, 1 = Music, 2 = Main Menu
    bool isMusicOn = true;                  // Tracks global audio state
    bool needsRestart = false; // <--- ADD THIS LINE

    GameState(sf::RenderWindow& win) : window(win) {}
};


void LoadAssets(GameState& condition);
void MainMenu(GameState& condition);
void CreditsMenu(GameState& condition);
void PauseMenu(GameState& condition); // --- NEW FUNCTION ---