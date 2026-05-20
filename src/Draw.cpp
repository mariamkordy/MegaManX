#include "Draw.h"
#include "Collision.h"

using namespace sf;
using namespace std;

void Draw(Player& player, sf::RenderWindow& window,
    std::vector<Ground>& grounds, std::vector<Wall>& walls,
    Background& background, Foreground& foreground,
    DashSmoke* dashsmoke, playerBullets* Bullets,
    std::vector<Checkpoint>& checkpoints,
    std::vector<Enemy>& enemies, std::vector<FireTrap>& fires,
    EneTextures& eneTex, sf::Texture& fireTexture)
{
    // 1. Background (furthest back)
    window.draw(background.bgSprite);

    // 2. Foreground/map layer
    window.draw(foreground.fgSprite);

    // 3. Grounds and Walls ON TOP of the map
    for (int i = 0; i < grounds.size(); i++)
        window.draw(grounds[i].rectangle);

    for (int i = 0; i < walls.size(); i++)
        window.draw(walls[i].rectangle);

    // 4. Enemies and traps
    drawEnemies(window, enemies, eneTex, player);
    drawFires(window, fires, fireTexture);

    // 5. Player
    window.draw(player.sprite);

    // 6. Dash smoke effects
    for (int i = 0; i < player.smokenumber; i++)
        if (dashsmoke[i].visible)
            window.draw(dashsmoke[i].display);

    // 7. Bullets
    for (int i = 0; i < 10; i++)
        if (Bullets[i].active)
            window.draw(Bullets[i].display);

    // 8. Checkpoints (UI-like markers, drawn last)
    for (int i = 0; i < checkpoints.size(); i++)
        window.draw(checkpoints[i].sprite);
}