#include "Combat.h"
#include "Enemy.h"
#include "player.h"

#include <vector>
//player attacking enemy


void checkBulletEnemyCollision(playerBullets Bullets[10], std::vector<Enemy>& enemies) {
	for (int i = 0; i < 10; i++) {
		if (!Bullets[i].active)continue;

		for (int j = 0; j <enemies.size(); j++) {
			if (!enemies[j].alive)continue;
			if (Bullets[i].display.getGlobalBounds().intersects(enemies[j].sprite.getGlobalBounds())) {
				enemies[j].health -= 10;
				Bullets[i].active = false;
				if (enemies[j].health <= 0) {
					enemies[j].alive = false;
				}
				break;
			}
		}

	}
}