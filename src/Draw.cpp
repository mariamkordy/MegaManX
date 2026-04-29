#include "Draw.h"
#include "Collision.h"

using namespace sf;
using namespace std;
void Draw(Player& player, sf::RenderWindow& window, const vector<Ground>& grounds, Background& background, Foreground& foreground,DashSmoke dashsmoke[100])
{
    window.clear();
    window.draw(background.bgSprite);
    window.draw(foreground.fgSprite);
    for (const auto& g : grounds) {
        window.draw(g.rectangle);
    }

    for (int i = 0; i < player.smokenumber; i++) {
        if (dashsmoke[i].visible ) {
            window.draw(dashsmoke[i].display);
        }
    }

    window.draw(player.sprite);

    window.display();
}