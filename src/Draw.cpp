#include "Draw.h"


void Draw(Player& player, sf::RenderWindow& window, sf::RectangleShape& ground, Background& background,DashSmoke dashsmoke[100])
{
    window.clear();

    window.draw(background.bgSprite);
    window.draw(ground);

    for (int i = 0; i < 15; i++) {
        if (dashsmoke[i].visible) {
            window.draw(dashsmoke[i].display);
        }
    }

    window.draw(player.sprite);

    window.display();
}