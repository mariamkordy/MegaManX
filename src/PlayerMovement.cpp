#include "PlayerMovement.h"

#include <iostream>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

void playerMovement(Player& player, float deltaTime, DashSmoke dashsmoke[100])
{
    float normalspeed = 300.f;
    float dashspeed = 1000.f;
    float currentspeed = normalspeed;
	//DASHING (INPUT AND UPDATE)

	if (!player.state == DASHING) {
		player.smokeTimer = 0.f;

	}
	if (Keyboard::isKeyPressed(Keyboard::A) && (player.state==RUNNING || player.isOnGround) && !player.state==STANDING){
		if (abs(player.velocity.x ) >1){
			player.isDashing = true;
			player.state = DASHING;

			player.dashTimer = player.dashduration;
		}

	}
	//DASHING (MOTION)		
	player.smokeTimer -= deltaTime;
	if (player.state == DASHING) {
		currentspeed = dashspeed;
		player.dashTimer -= deltaTime;
		if (player.dashTimer <= 0) {
			player.isDashing = false;
		}


		if (player.smokeTimer <= 0) {
			for (int i = 0; i < player.smokenumber; i++) {

				if (dashsmoke[i].visible == false) {
					dashsmoke[i].visible = true;
					player.smokeTimer = 0.04f;

					dashsmoke[i].Position = player.sprite.getPosition();
					dashsmoke[i].display.setOrigin(2, 5);

					Vector2f spawnpos = player.sprite.getPosition();
					if (player.facingRight) {
						spawnpos.x -= 20.0f;
					}
					else {
						spawnpos.x += 120.0f;
					}
					spawnpos.y += 60.0f;

					dashsmoke[i].display.setPosition(spawnpos);

					break;
				}
			}
		}

	}
	player.velocity.x = 0.f;
    if (Keyboard::isKeyPressed(Keyboard::Up) && player.isOnGround)
    {
        player.velocity.y = -850.f;
        player.isOnGround = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        player.velocity.x = -currentspeed;
        player.facingRight = false;

    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        player.velocity.x = currentspeed;
        player.facingRight = true;

    }

	if (!player.isOnGround) {
		player.state = JUMPING;
	}	
	else if (player.isDashing){
		player.state = DASHING;
	}
	else if (abs(player.velocity.x) > 1.0f  ) { //moves fast enough for us to consider it to be running
		player.state = RUNNING;
	}
	else {
		player.state = STANDING;
	}
	
}