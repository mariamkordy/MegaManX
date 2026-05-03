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

			float distance = getDist(Bullets[i].display.getPosition(),enemies[j].pos);
			if (distance <= 100) {
				Bullets[i].active = false;
				enemies[j].health -= 50;
	
				if (enemies[j].health <= 0) {
					enemies[j].dying = true;
					enemies[j].animFrame = 0;
				}
				break;
			}
		}

	}
}