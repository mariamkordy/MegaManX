#include "Draw.h"
#include "Collision.h"

using namespace sf;
using namespace std;
void Draw(Player& player, sf::RenderWindow& window, const vector<Ground>& grounds, const vector<Wall>& walls, Background& background, Foreground& foreground,DashSmoke dashsmoke[100], vector<Checkpoint>& checkpoints)
{
    window.draw(background.bgSprite);
    window.draw(foreground.fgSprite);
    for (const auto& g : grounds) {
        window.draw(g.rectangle);
    }
    for (const auto& w : walls) {
        window.draw(w.rectangle);
    }

    for (int i = 0; i < player.smokenumber; i++) {
        if (dashsmoke[i].visible ) {
            window.draw(dashsmoke[i].display);
        }
    }

    window.draw(player.sprite);
    for (int i = 0; i < checkpoints.size(); i++)
        window.draw(checkpoints[i].shape);

}