#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>


// --- MENU FUNCTIONS ---

// '&' symbol passes the struct by reference
void SetupSpriteText(GameState& condition, std::string word, float x, float y) {
    for (int i = 0; i < (int)word.length(); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z') {
            condition.textSprites[i].setTexture(condition.fontSheetTex);

            int charIndex = word[i] - 'A';
            condition.textSprites[i].setTextureRect(sf::IntRect(charIndex * 8, 0, 7, 7));
            condition.textSprites[i].setScale(6.0f, 6.0f);
        }
        condition.textSprites[i].setPosition(x + (i * 45), y);
    }
}

void LoadAssets(GameState& condition) {
    condition.logoTex.loadFromFile("assets/textures/GAME START.png");
    condition.logoSprite.setTexture(condition.logoTex);

    condition.logoSprite.setScale(4.5f, 4.5f);
    condition.logoSprite.setOrigin(condition.logoSprite.getLocalBounds().width / 2.0f, 0);
    condition.logoSprite.setPosition(condition.windowSize.x / 2.0f, 50.f);

    condition.cursorTex.loadFromFile("assets/textures/standing.png");
    condition.cursorSprite.setTexture(condition.cursorTex);
    condition.cursorSprite.setTextureRect(sf::IntRect(0, 0, 36, 52));

    condition.cursorSprite.setScale(3.5f, 3.5f);

    condition.fontSheetTex.loadFromFile("assets/textures/font.png");

    // Pass the state into the setup function
    SetupSpriteText(condition, "GAME STARTw", 930.f, 750.f);


    if (condition.startBuffer.loadFromFile("assets/sounds/level sound.mp3")) {
        condition.startSound.setBuffer(condition.startBuffer);
        condition.startSound.setLoop(true);
    }
    else {
        std::cout << "FAILED TO LOAD START SOUND\n";
    }
}


void MainMenu(GameState& condition) {
    // You can use the dot (.) again!
    while (condition.window.pollEvent(condition.e)) {
        if (condition.e.type == sf::Event::Closed) condition.window.close();
        if (condition.e.type == sf::Event::KeyPressed && condition.e.key.code == sf::Keyboard::Enter) {
            condition.menuIndex = 1;
            condition.startSound.play();
        }
    }

    condition.cursorSprite.setPosition(condition.textSprites[0].getPosition().x - 180.f, condition.textSprites[0].getPosition().y - 65.f);

    condition.window.clear(sf::Color::Black);
    condition.window.draw(condition.logoSprite);

    for (int i = 0; i < 10; i++) {
        condition.window.draw(condition.textSprites[i]);
    }

    condition.window.draw(condition.cursorSprite);
    condition.window.display();
}