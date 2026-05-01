#include "PlayerMovement.h"

#include <iostream>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

//RESPONSIBLE FOR INPUT DEPENDENT MOTION AND STATE MODIFICATION


void playerMovement(Player& player, float deltaTime, DashSmoke dashsmoke[100])

{
	
	if (player.isOnGround == true)
	cout << ""<< endl;
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

	//PLAYER SHOOTING ANIMATION

	if (player.state== TELEPORT) {

		player.sprite.setTexture(player.teleport);//done
		//cutting the sprite
		player.sprite.setTextureRect(IntRect(player.shootingindex * 0, 0, 112, 115));
		player.shootingindex = (player.shootingindex + 1) % 13;

	} 
	else if (player.state== JUMPSHOOTING) {
		//linking player with sprite
		player.sprite.setTexture(player.jump);
		if (player.velocity.y < 0) {

			if (player.jumpshootingindex < 3) {
				player.jumpshootingindex++;
			}
			else {
				player.jumpshootingindex = 4;
			}
		}
		//cutting the sprite
		player.sprite.setTextureRect(IntRect(player.jumpshootingindex * 120, 0, 120, 125));

	}
	else if (player.state== RUNSHOOTING) {
		//linking player with sprite
		player.sprite.setTexture(player.shootingwhilerunning);
		//cutting the sprite
		player.sprite.setTextureRect(IntRect(player.shootingindex * 112, 0, 112, 115));
		player.shootingindex = (player.shootingindex + 1) % 10;
	}
	else if (player.state==DASHSHOOTING) {
		//linking player with the sprite
		player.sprite.setTexture(player.dashshooting);
		//cutting the sprite
		player.sprite.setTextureRect(IntRect(player.shootingindex * 160, 0, 160, 130));
		player.shootingindex = 2;

	}










	player.velocity.x = 0.f;
    if (Keyboard::isKeyPressed(Keyboard::Up) && player.isOnGround)
    {
        player.velocity.y = -850.f;
        player.isOnGround = false;
		//shooting?
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.state = JUMPSHOOTING;
		}
        //////////  	
    }

	if (Keyboard::isKeyPressed(Keyboard::Up) && !player.isOnGround && player.isOnWall)
	{
		player.velocity.y = -850.f;
		player.isOnGround = false;
	}
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        player.velocity.x = -currentspeed;
        player.facingRight = false;
		//shooting?
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.state = RUNSHOOTING;
		}
	
		/////////////

    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        player.velocity.x = currentspeed;
        player.facingRight = true;
		//shooting?
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			player.state = RUNSHOOTING;
		}
		
		/////////////

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