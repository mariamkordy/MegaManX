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
    EneTextures& eneTex, sf::Texture& fireTexture) // استخدمنا eneTex هنا
{
    window.draw(background.bgSprite);

    for (int i = 0; i < grounds.size(); i++) {
        window.draw(grounds[i].rectangle);
    }

    window.draw(foreground.fgSprite);

    // نداء الدوال باستخدام الأسماء المطابقة للهيدر والـ main
    drawEnemies(window, enemies, eneTex, player); // اتأكدي إنها eneTex مش tex
    drawFires(window, fires, fireTexture); // اتأكدي إنها fireTexture

    // رسم تأثيرات الـ Dash
    for (int i = 0; i < player.smokenumber; i++) {
        if (dashsmoke[i].visible) {
            window.draw(dashsmoke[i].display);
        }
    }

    // رسم رصاص اللاعب
    for (int i = 0; i < 10; i++) {
        if (Bullets[i].active) {
            window.draw(Bullets[i].display);
        }
    }

    window.draw(player.sprite);

    for (int i = 0; i < checkpoints.size(); i++) {
        window.draw(checkpoints[i].sprite);
    }
}