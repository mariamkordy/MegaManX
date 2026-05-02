#include "Draw.h"
#include "Collision.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

void Draw(Player& player, sf::RenderWindow& window, std::vector<Ground>& grounds,
    std::vector<Wall>& walls, Background& background, Foreground& foreground,
    DashSmoke dashsmoke[], std::vector<Enemy>& enemies, std::vector<FireTrap>& fires,
    EneTextures& tex, sf::Texture& fireTex)
{
    window.clear();

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
    window.draw(player.sprite);

    window.display();
}