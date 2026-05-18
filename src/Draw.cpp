#include "Draw.h"
#include "Collision.h"

using namespace sf;
using namespace std;
void Draw(Player& player, sf::RenderWindow& window, const vector<Ground>& grounds, const vector<Wall>& walls, Background& background, Foreground& foreground, DashSmoke dashsmoke[100], playerBullets Bullets[10], vector<Checkpoint>& checkpoints, std::vector<Enemy>& enemies, std::vector<FireTrap>& fires,
    EneTextures& tex, sf::Texture& fireTex)
{
    window.draw(background.bgSprite);
    for (int i = 0; i < grounds.size(); i++) {
        window.draw(grounds[i].rectangle);
    }
    window.draw(foreground.fgSprite);

    drawEnemies(window, enemies, tex, player.sprite.getPosition());

    drawFires(window, fires, fireTex);

    for (int i = 0; i < 15; i++) {
        if (dashsmoke[i].visible) {
            window.draw(dashsmoke[i].display);
        }
    }
    for (const auto& g : grounds) {
        window.draw(g.rectangle);
    }
    for (const auto& w : walls) {
        window.draw(w.rectangle);
    }

    for (int i = 0; i < player.smokenumber; i++) {
        if (dashsmoke[i].visible) {
            window.draw(dashsmoke[i].display);
        }
    }

    for (int i = 0; i < 10; i++) {
        if (Bullets[i].active) {
            window.draw(Bullets[i].display);
        }
    }

    for (int i = 0; i < checkpoints.size(); i++)
        window.draw(checkpoints[i].sprite);    
    window.draw(player.sprite);

}