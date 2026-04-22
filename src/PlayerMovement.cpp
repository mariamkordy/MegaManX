#include "PlayerMovement.h"
#include <SFML/Window/Keyboard.hpp>

void playerMovement(Player& player, bool jumpKeyReleased,float deltaTime,DashSmoke dashsmoke[15])
{
    float normalspeed = 300.f;
    float dashspeed = 1000.f;
    float currentspeed = normalspeed;
	player.isDashing = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		player.isDashing = true;
		player.dashTimer = player.dashduration;
	}

	if (player.isDashing && player.isRunning) {
		currentspeed = dashspeed;
		
		player.dashTimer -= deltaTime;
		if (player.dashTimer <= 0) {
			player.isDashing = false;
		}

		player.smokeTimer -= deltaTime;
		if (player.smokeTimer <= 0) {
			for (int i = 0; i < 15; i++) {
				if (dashsmoke[i].visible == false) {		
					dashsmoke[i].visible = true;				
					player.smokeTimer = 0.6f;//

					dashsmoke[i].Position = player.sprite.getPosition();
					dashsmoke[i].display.setOrigin(7, 31);

					sf::Vector2f spawnpos = player.sprite.getPosition();
					if (player.facingRight) {
						spawnpos.x -= 20.0f;
					}
					else {
						spawnpos.x += 20.0f;
					}
					spawnpos.y += 60.0f;
					
					dashsmoke[i].display.setPosition(spawnpos);
					
					break;
				}
			}
		}

	}


    player.isRunning = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player.isOnGround)
    {
        player.velocity.y = -850.f;
        player.isOnGround = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.velocity.x = -currentspeed;
        player.isRunning = true;
        player.facingRight = false;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.velocity.x = currentspeed;
        player.isRunning = true;
        player.facingRight = true;
    }
    else {
        player.velocity.x = 0.f;
    }
}