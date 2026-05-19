/*#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
//

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
*/


#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

void LoadAssets(GameState& condition) {
    // 1. Load the Menu Background Scene
    if (!condition.backgroundTex.loadFromFile("assets/textures/mainmenu.png")) {
        std::cerr << "ERROR: Could not find assets/textures/mainmenu.png\n";
    }
    condition.backgroundSprite.setTexture(condition.backgroundTex);

    // FIX: Force the background image to scale perfectly to your 1920x1080 window dimensions
    float scaleX = condition.windowSize.x / condition.backgroundSprite.getLocalBounds().width;
    float scaleY = condition.windowSize.y / condition.backgroundSprite.getLocalBounds().height;
    condition.backgroundSprite.setScale(scaleX, scaleY);

    // 2. Load the Credits Screen Image
    if (!condition.creditsTex.loadFromFile("assets/textures/credits.png")) {
        std::cerr << "ERROR: Could not find assets/textures/credits.png\n";
    }
    condition.creditsSprite.setTexture(condition.creditsTex);
    // Scale credits screen as well just in case
    float credScaleX = condition.windowSize.x / condition.creditsSprite.getLocalBounds().width;
    float credScaleY = condition.windowSize.y / condition.creditsSprite.getLocalBounds().height;
    condition.creditsSprite.setScale(credScaleX, credScaleY);

    // 3. Configure the Selection Highlight Box Outline
    condition.highlightBox.setFillColor(sf::Color::Transparent);
    condition.highlightBox.setOutlineColor(sf::Color::White);
    condition.highlightBox.setOutlineThickness(4.0f);

    // 4. Load Menu Audio Transition
    if (condition.startBuffer.loadFromFile("assets/sounds/level sound.mp3")) {
        condition.startSound.setBuffer(condition.startBuffer);
        condition.startSound.setLoop(true);
    }
    else {
        std::cerr << "FAILED TO LOAD START SOUND\n";
    }


    // Inside LoadAssets(GameState& condition) ...

    // Load Pause Menu Image
    if (!condition.pauseTex.loadFromFile("assets/textures/pausemenu.png")) {
        std::cerr << "ERROR: Could not find assets/textures/pausemenu.png\n";
    }
    condition.pauseSprite.setTexture(condition.pauseTex);

    // Scale pause menu to 1920x1080
    float pauseScaleX = condition.windowSize.x / condition.pauseSprite.getLocalBounds().width;
    float pauseScaleY = condition.windowSize.y / condition.pauseSprite.getLocalBounds().height;
    condition.pauseSprite.setScale(pauseScaleX, pauseScaleY);

    // Setup Pause Menu Highlight Boxes
    condition.pauseHighlightBox.setFillColor(sf::Color::Transparent);
    condition.pauseHighlightBox.setOutlineColor(sf::Color::White);
    condition.pauseHighlightBox.setOutlineThickness(4.0f);

    // FIX: Make the ON/OFF indicator an empty outline box instead of a solid block
    condition.musicStatusBox.setFillColor(sf::Color::Transparent);
    condition.musicStatusBox.setOutlineColor(sf::Color::White);
    condition.musicStatusBox.setOutlineThickness(4.0f);

    // Setup the smaller box that shows if music is ON or OFF
    condition.musicStatusBox.setFillColor(sf::Color(255, 255, 255, 100)); // Semi-transparent white
}

void MainMenu(GameState& condition) {
    // 1. Menu Event/Input Processing
    while (condition.window.pollEvent(condition.e)) {
        if (condition.e.type == sf::Event::Closed) {
            condition.window.close();
        }

        if (condition.e.type == sf::Event::KeyPressed) {
            // Navigate Up
            if (condition.e.key.code == sf::Keyboard::Up || condition.e.key.code == sf::Keyboard::W) {
                condition.currentSelection = (condition.currentSelection - 1 + 3) % 3;
            }
            // Navigate Down
            if (condition.e.key.code == sf::Keyboard::Down || condition.e.key.code == sf::Keyboard::S) {
                condition.currentSelection = (condition.currentSelection + 1) % 3;
            }
            // Confirm Selection
            if (condition.e.key.code == sf::Keyboard::Enter) {
                if (condition.currentSelection == 0) {       // START GAME
                    condition.menuIndex = 1;
                    condition.startSound.play();
                }
                else if (condition.currentSelection == 1) {  // CREDITS
                    condition.menuIndex = 2;                  // Forces state switch to Credits Menu
                }
                else if (condition.currentSelection == 2) {  // EXIT
                    condition.window.close();
                }
            }
        }
    }

    // 2. RE-CALIBRATED COORDINATES
    // These coordinates account for the stretched texture coordinates on a 1920x1080 window frame.
    if (condition.currentSelection == 0) {
        // Frames "START GAME" perfectly
        condition.highlightBox.setPosition(210.f, 635.f);
        condition.highlightBox.setSize(sf::Vector2f(440.f, 70.f));
    }
    else if (condition.currentSelection == 1) {
        // Frames "CREDITS" perfectly
        condition.highlightBox.setPosition(305.f, 715.f);
        condition.highlightBox.setSize(sf::Vector2f(250.f, 50.f));
    }
    else if (condition.currentSelection == 2) {
        // Frames "EXIT" perfectly
        condition.highlightBox.setPosition(355.f, 785.f);
        condition.highlightBox.setSize(sf::Vector2f(150.f, 50.f));
    }

    // 3. Render the Main Menu
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
            // Navigate Options
            if (condition.e.key.code == sf::Keyboard::Up || condition.e.key.code == sf::Keyboard::W) {
                condition.pauseSelection = (condition.pauseSelection - 1 + 3) % 3;
            }
            if (condition.e.key.code == sf::Keyboard::Down || condition.e.key.code == sf::Keyboard::S) {
                condition.pauseSelection = (condition.pauseSelection + 1) % 3;
            }

            // Toggle Music
            if (condition.pauseSelection == 1 &&
                (condition.e.key.code == sf::Keyboard::Left || condition.e.key.code == sf::Keyboard::Right || condition.e.key.code == sf::Keyboard::Enter)) {

                condition.isMusicOn = !condition.isMusicOn;

                if (condition.isMusicOn) {
                    condition.startSound.play();  // Resumes track exactly where it left off
                }
                else {
                    condition.startSound.pause(); // Freezes track
                }
            }
            // Confirm Selection
            else if (condition.e.key.code == sf::Keyboard::Enter) {
                if (condition.pauseSelection == 0) {       // RESUME
                    condition.menuIndex = 1;
                }
                else if (condition.pauseSelection == 2) {  // RETURN TO MAIN MENU
                    condition.startSound.stop();           // Halts music completely
                    condition.menuIndex = 0;               // Go to Main Menu
                    condition.currentSelection = 0;        // Reset main menu cursor
                    condition.needsRestart = true;         // Tell main.cpp to restart the level!
                }
            }

            // Unpause shortcut
            if (condition.e.key.code == sf::Keyboard::P || condition.e.key.code == sf::Keyboard::Escape) {
                condition.menuIndex = 1;
            }
        }
    }

    // --- MATHEMATICALLY SCALED COORDINATES ---
    // Mapped from native 1380x752 to your 1920x1080 window
// --- PRECISION ALIGNED COORDINATES ---

    if (condition.pauseSelection == 0) {
        // RESUME
        // X=830 (Horizontal), Y=440 (Vertical), Width=260, Height=60
        condition.pauseHighlightBox.setPosition(865.f, 420.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(270.f, 60.f));
    }
    else if (condition.pauseSelection == 1) {
        // MUSIC 
        // X=700, Y=560, Width=520, Height=60
        condition.pauseHighlightBox.setPosition(700.f, 530.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(640.f, 60.f));
    }
    else if (condition.pauseSelection == 2) {
        // RETURN TO MAIN MENU
        // X=560, Y=680, Width=800, Height=60
        condition.pauseHighlightBox.setPosition(600.f, 640.f);
        condition.pauseHighlightBox.setSize(sf::Vector2f(800.f, 60.f));
    }

    // ON/OFF INDICATOR BOXES (Aligning with the Music line)
    if (condition.isMusicOn) {
        // Frames "ON"
        condition.musicStatusBox.setPosition(1020.f, 530.f);
        condition.musicStatusBox.setSize(sf::Vector2f(80.f, 60.f));
    }
    else {
        // Frames "OFF"
        condition.musicStatusBox.setPosition(1194.f, 530.f);
        condition.musicStatusBox.setSize(sf::Vector2f(130.f, 60.f));
    }

    // Render Window Elements
    condition.window.clear(sf::Color::Black);
    condition.window.draw(condition.pauseSprite);
    condition.window.draw(condition.pauseHighlightBox);
    condition.window.draw(condition.musicStatusBox);
    condition.window.display();
}