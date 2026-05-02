#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>

struct GameState {
    sf::RenderWindow& window; // Changed from '*' to '&'
    sf::Texture logoTex, cursorTex, fontSheetTex;
    sf::Sprite logoSprite, cursorSprite;
    sf::Sprite textSprites[20];
    sf::Event e;
    int menuIndex = 0;
    sf::Vector2f windowSize{ 1920.f, 1080.f };
    sf::SoundBuffer startBuffer;
    sf::Sound startSound;
    sf::Clock clock1;
    float deltaTime = 0.f;
    sf::View view;

    // We must add a constructor to initialize the reference
    GameState(sf::RenderWindow& win) : window(win) {}
};

void LoadAssets(GameState& condition);
void SetupSpriteText(GameState& condition, std::string word, float x, float y);
void MainMenu(GameState& condition);