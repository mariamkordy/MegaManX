#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
    Player myplayer;
    myplayer.circle.setRadius(50.f);
    myplayer.circle.setPosition(100.f, 100.f);

    sf::RectangleShape ground(sf::Vector2f(800.f, 100.f));
    ground.setPosition(0.f, 550.f);

    sf::RenderWindow window(sf::VideoMode(800, 600), "MegaManX");
    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player_movement(myplayer, deltaTime);
        jump(myplayer);
        gravity(myplayer, deltaTime);
        checkGround(myplayer, ground);
        playerpos(myplayer);
        collision_with_frame(myplayer);

        window.clear(sf::Color::Black);

        window.draw(myplayer.circle);
        window.draw(ground);

        window.display();
    }

    return 0;
}