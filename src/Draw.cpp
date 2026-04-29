#include "Draw.h"

using namespace sf;
void Draw(Player& player, sf::RenderWindow& window, sf::RectangleShape& ground, Background& background,DashSmoke dashsmoke[100])
{
    window.clear();

    //sf::Vector2f targetSize = sf::Vector2f(window.getSize());
    //sf::Vector2f photoSize = background.bgSprite.getLocalBounds().getSize();

    //background.bgSprite.setScale(targetSize.x / photoSize.x, targetSize.y / photoSize.y);
    window.draw(background.bgSprite);
    window.draw(ground);

    for (int i = 0; i < player.smokenumber; i++) {
        if (dashsmoke[i].visible ) {
            window.draw(dashsmoke[i].display);
        }
    }

    window.draw(player.sprite);

    window.display();
}