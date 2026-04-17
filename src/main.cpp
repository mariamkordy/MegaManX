#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Player.h"
#include "Background.h"
#include "PlayerMovement.h"
#include "PlayerPhysics.h"
#include "UpdateAnimation.h"
#include "Collision.h"
#include "Camera.h"
#include "Draw.h"
#include "GameInit.h"

int main()
{
    Player player;
    Background background;
    sf::RectangleShape ground;
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Mega Man X", sf::Style::Fullscreen);
    sf::View view;

    sf::Clock clock;
    float deltaTime;

    bool jumpKeyReleased = true;

    Start(player, view, window, ground, background);

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        //CLOSING THE WINDOW
        sf::Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
            else if(ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        playerMovement(player, jumpKeyReleased);
        playerPhysics(player, deltaTime);
        collision(player, ground);
        updateAnimation(player, deltaTime, jumpKeyReleased);
        camera(player, view, window, background);
        Draw(player, window, ground, background);
    }

    return 0;
}