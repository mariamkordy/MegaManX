#include "Draw.h"

void Draw(Player& player, sf::RenderWindow& window, sf::RectangleShape& ground, Background& background)
{
    window.clear();

    window.draw(background.bgSprite);
    window.draw(ground);
    window.draw(player.sprite);

    window.display();
}