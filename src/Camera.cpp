#include "Camera.h"

void camera(Player& player, sf::View& view, sf::RenderWindow& window, Background& background)
{
    view.setCenter(player.sprite.getPosition());
    window.setView(view);

    background.bgSprite.setPosition(
        view.getCenter().x * 0.5f - view.getSize().x / 2,
        50.f
    );
}