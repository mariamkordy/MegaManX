#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void LoadAssets(GameState& condition) {
    // 1. Load the Menu Background Scene
    if (!condition.backgroundTex.loadFromFile("assets/textures/mainmenu.png")) {
        std::cerr << "ERROR: Could not find assets/textures/mainmenu.png\n";
    }
    condition.backgroundSprite.setTexture(condition.backgroundTex);

    // Scale background image to 1920x1080
    float scaleX = condition.windowSize.x / condition.backgroundSprite.getLocalBounds().width;
    float scaleY = condition.windowSize.y / condition.backgroundSprite.getLocalBounds().height;
    condition.backgroundSprite.setScale(scaleX, scaleY);

    // 2. Load the Credits Screen Image
    if (!condition.creditsTex.loadFromFile("assets/textures/credits.png")) {
        std::cerr << "ERROR: Could not find assets/textures/credits.png\n";
    }
    condition.creditsSprite.setTexture(condition.creditsTex);
    float credScaleX = condition.windowSize.x / condition.creditsSprite.getLocalBounds().width;
    float credScaleY = condition.windowSize.y / condition.creditsSprite.getLocalBounds().height;
    condition.creditsSprite.setScale(credScaleX, credScaleY);

    // 3. Configure the Selection Highlight Box Outline
    condition.highlightBox.setFillColor(sf::Color::Transparent);
    condition.highlightBox.setOutlineColor(sf::Color::White);
    condition.highlightBox.setOutlineThickness(4.0f);

    // 4. Load Menu Audio Transition
    if (condition.startBuffer.loadFromFile("assets/sounds/level music.mp3")) {
        condition.startSound.setBuffer(condition.startBuffer);
        condition.startSound.setLoop(true);
    }
    else {
        std::cerr << "FAILED TO LOAD START SOUND\n";
    }

    if (condition.menuBuffer.loadFromFile("assets/sounds/main music.wav")) {
        condition.menuSound.setBuffer(condition.menuBuffer);
        condition.menuSound.setLoop(true);
        condition.menuSound.play();
    }
    else {
        std::cerr << "FAILED TO LOAD MENU SOUND\n";
    }

    // 5. Load Pause Menu Assets
    if (!condition.pauseTex.loadFromFile("assets/textures/pausemenu.png")) {
        std::cerr << "ERROR: Could not find assets/textures/pausemenu.png\n";
    }
    condition.pauseSprite.setTexture(condition.pauseTex);

    // Scale pause menu
    float pauseScaleX = condition.windowSize.x / condition.pauseSprite.getLocalBounds().width;
    float pauseScaleY = condition.windowSize.y / condition.pauseSprite.getLocalBounds().height;
    condition.pauseSprite.setScale(pauseScaleX, pauseScaleY);

    // Setup Pause Menu Boxes
    condition.pauseHighlightBox.setFillColor(sf::Color::Transparent);
    condition.pauseHighlightBox.setOutlineColor(sf::Color::White);
    condition.pauseHighlightBox.setOutlineThickness(4.0f);

    condition.musicStatusBox.setFillColor(sf::Color(255, 255, 255, 100));
    condition.musicStatusBox.setOutlineColor(sf::Color::White);
    condition.musicStatusBox.setOutlineThickness(4.0f);
}

void MainMenu(GameState& condition) {
    while (condition.window.pollEvent(condition.e)) {
        if (condition.e.type == sf::Event::Closed) {
            condition.window.close();
        }

        if (condition.e.type == sf::Event::KeyPressed) {
            if (condition.e.key.code == sf::Keyboard::Up || condition.e.key.code == sf::Keyboard::W) {
                condition.currentSelection = (condition.currentSelection - 1 + 3) % 3;
            }
            if (condition.e.key.code == sf::Keyboard::Down || condition.e.key.code == sf::Keyboard::S) {
                condition.currentSelection = (condition.currentSelection + 1) % 3;
            }
            if (condition.e.key.code == sf::Keyboard::Enter) {
                if (condition.currentSelection == 0) {
                    condition.menuSound.stop();
                    condition.menuIndex = 1;
                    condition.startSound.play();
                }
                else if (condition.currentSelection == 1) {
                    condition.menuIndex = 2;
                }
                else if (condition.currentSelection == 2) {
                    condition.window.close();
                }
            }
        }
    }

    if (condition.currentSelection == 0) {
        condition.highlightBox.setPosition(210.f, 635.f);
        condition.highlightBox.setSize(sf::Vector2f(440.f, 70.f));
    }
    else if (condition.currentSelection == 1) {
        condition.highlightBox.setPosition(305.f, 715.f);
        condition.highlightBox.setSize(sf::Vector2f(250.f, 50.f));
    }
    else if (condition.currentSelection == 2) {
        condition.highlightBox.setPosition(355.f, 785.f);
        condition.highlightBox.setSize(sf::Vector2f(150.f, 50.f));
    }

    condition.window.clear(sf::Color::Black);
    condition.window.draw(condition.backgroundSprite);
    condition.window.draw(condition.highlightBox);
    condition.window.display();
}

void CreditsMenu(GameState& condition) {
    while (condition.window.pollEvent(condition.e)) {
        if (condition.e.type == sf::Event::Closed) {
            condition.window.close();
        }
        if (condition.e.type == sf::Event::KeyPressed) {
            if (condition.e.key.code == sf::Keyboard::Escape || condition.e.key.code == sf::Keyboard::BackSpace) {
                condition.menuIndex = 0;
            }
        }
    }
    condition.window.clear(sf::Color::Black);
    condition.window.draw(condition.creditsSprite);
    condition.window.display();
}

void PauseMenu(GameState& condition) {
    while (condition.window.pollEvent(condition.e)) {
        if (condition.e.type == sf::Event::Closed) {
            condition.window.close();
        }

        if (condition.e.type == sf::Event::KeyPressed) {
            if (condition.e.key.code == sf::Keyboard::Up || condition.e.key.code == sf::Keyboard::W) {
                condition.pauseSelection = (condition.pauseSelection - 1 + 3) % 3;
            }
            if (condition.e.key.code == sf::Keyboard::Down || condition.e.key.code == sf::Keyboard::S) {
                condition.pauseSelection = (condition.pauseSelection + 1) % 3;
            }

            if (condition.pauseSelection == 1 &&
                (condition.e.key.code == sf::Keyboard::Left || condition.e.key.code == sf::Keyboard::Right || condition.e.key.code == sf::Keyboard::Enter)) {
                condition.isMusicOn = !condition.isMusicOn;
                if (condition.isMusicOn) condition.startSound.play();
                else condition.startSound.pause();
            }
            else if (condition.e.key.code == sf::Keyboard::Enter) {
                if (condition.pauseSelection == 0) {
                    condition.menuIndex = 1;
                }
                else if (condition.pauseSelection == 2) {
                    condition.startSound.stop();
                    condition.menuSound.play();
                    condition.menuIndex = 0;
                    condition.currentSelection = 0;
                    condition.needsRestart = true;
                }
            }

            if (condition.e.key.code == sf::Keyboard::P || condition.e.key.code == sf::Keyboard::Escape) {
                condition.menuIndex = 1;
            }
        }
    }

    if (condition.pauseSelection == 0) {
        condition.pauseHighlightBox.setPosition(865.f, 420.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(270.f, 60.f));
    }
    else if (condition.pauseSelection == 1) {
        condition.pauseHighlightBox.setPosition(700.f, 530.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(640.f, 60.f));
    }
    else if (condition.pauseSelection == 2) {
        condition.pauseHighlightBox.setPosition(600.f, 640.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(800.f, 60.f));
    }

    if (condition.isMusicOn) {
        condition.musicStatusBox.setPosition(1020.f, 530.f);
        condition.musicStatusBox.setSize(sf::Vector2f(80.f, 60.f));
    }
    else {
        condition.musicStatusBox.setPosition(1194.f, 530.f);
        condition.musicStatusBox.setSize(sf::Vector2f(130.f, 60.f));
    }

    condition.window.clear(sf::Color::Black);
    condition.window.draw(condition.pauseSprite);
    condition.window.draw(condition.pauseHighlightBox);
    condition.window.draw(condition.musicStatusBox);
    condition.window.display();
}