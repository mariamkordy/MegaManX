#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void gravity(Player& player, float deltaTime)
{
    float gravityForce = 1200.f;

    if (!player.isGrounded)
    {
        player.velocity.y += gravityForce * deltaTime;
    }
    else
    {
        player.velocity.y = 0;
    }

    player.circle.move(0.f, player.velocity.y * deltaTime);
}


void checkGround(Player& player, sf::RectangleShape& ground)
{
    if (player.circle.getGlobalBounds().intersects(ground.getGlobalBounds()))
    {
        float groundTop = ground.getPosition().y;
        float playerHeight = player.circle.getRadius() * 2;

        player.circle.setPosition(
            player.circle.getPosition().x,
            groundTop - playerHeight
        );

        player.isGrounded = true;
        player.velocity.y = 0;
    }
    else
    {
        player.isGrounded = false;
    }
}

void player_movement(Player& player, float deltaTime)
{
    float speed = 200.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player.circle.move(-speed * deltaTime, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player.circle.move(speed * deltaTime, 0.f);
}


void jump(Player& player)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.isGrounded)
    {
        player.velocity.y = -600.f;
        player.isGrounded = false;
    }
}


void playerpos(Player& player)
{
    sf::Vector2f pos = player.circle.getPosition();
    player.position.x = pos.x;
    player.position.y = pos.y;
}


void collision_with_frame(Player& player)
{
    float radius = player.circle.getRadius();

    if (player.position.x < 0)
        player.position.x = 0;

    if (player.position.x + (2 * radius) > 800)
        player.position.x = 800 - (2 * radius);

    if (player.position.y < 0)
        player.position.y = 0;

    if (player.position.y + (2 * radius) > 600)
        player.position.y = 600 - (2 * radius);

    player.circle.setPosition(player.position.x, player.position.y);
}


