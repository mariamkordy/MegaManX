#include "UpdateAnimation.h"
#include <iostream>

using namespace sf;
using namespace std;
//NEVER SET STATES IN THIS FILE. STATES SHOULD ONLY BE MODIFIED IN PlayerMovement.cpp


void updateAnimation(Player& player, float deltaTime) {
    if (player.isOnGround)
    {
        player.jumpIndex = 0;
        player.jumpTimer = 0.f;

        // Dashing (only while running on the ground)
     if (player.state == DASHING)
    {
        player.sprite.setTexture(player.dashrunAnimation);

        if (player.facingRight)
            player.sprite.setTextureRect(IntRect(0, 0, 41, 42));
        else
            player.sprite.setTextureRect(IntRect(41, 0, -41, 42));
    }
    else if (player.state == RUNSHOOTING) {

            //linking player with sprite
            player.sprite.setTexture(player.shootingwhilerunning);
            //timer check
            player.runTimer += deltaTime;

            if (player.runTimer > 0.1f) {
                player.shootingindex = player.shootingindex = (player.shootingindex + 1) % 9;
                player.runTimer = 0.f;
            }

            if (player.facingRight)
                //cutting the sprite
                player.sprite.setTextureRect(IntRect(player.shootingindex * 44, 0, 44, 42));

            else {
                player.sprite.setTextureRect(IntRect(player.shootingindex * 44 + 44, 0, -44, 42));
            }

        }
    else if (player.state == IDLESHO) {
         player.sprite.setTexture(player.idlesho);

         if (player.facingRight)
             player.sprite.setTextureRect(IntRect(0, 0, 36, 52));
         else
             player.sprite.setTextureRect(IntRect(36, 0, -36, 52));
         player.shootingindex = 0;
     }

      
        // Running
        else if (player.state == RUNNING)
        {
            if (player.sprite.getTexture() != &player.runningAnimation)
                player.sprite.setTexture(player.runningAnimation);

            player.runTimer += deltaTime;

            int maxRunFrames = player.runningAnimation.getSize().x / 36;

            if (player.runTimer > 0.05f) {
                player.runIndex++;
                if (player.runIndex >= maxRunFrames)
                    player.runIndex = 0;
                player.runTimer = 0.f;
            }

            if (player.facingRight)
                player.sprite.setTextureRect(IntRect(player.runIndex * 36, 0, 36, 52));
            else
                player.sprite.setTextureRect(IntRect(player.runIndex * 36 + 36, 0, -36, 52));
        }
       
        // Standing
        else if (player.state == STANDING)
        {
            if (player.sprite.getTexture() != &player.standingAnimation)
                player.sprite.setTexture(player.standingAnimation);

            if (player.facingRight)
                player.sprite.setTextureRect(IntRect(0, 0, 36, 52));
            else
                player.sprite.setTextureRect(IntRect(36, 0, -36, 52));

            player.runIndex = 0;
        }
    }
    // isOnGround = false, Mid-air
    else
    {

        if (player.state == JUMPSHOOTING) {
            //linking player with sprite
            player.sprite.setTexture(player.jump);
            if (player.velocity.y < 0) {

                if (player.facingRight)
                    player.sprite.setTextureRect(IntRect(0, 0, 37, 50));
                else
                    player.sprite.setTextureRect(IntRect(37, 0, -37, 50));
                player.jumpshootingindex = 0;


               /* if (player.jumpshootingindex < 2) {
                    player.jumpshootingindex++;
                }
                else {
                    player.jumpshootingindex = 2;
                }
                if (player.facingRight) {
                    player.sprite.setTextureRect(IntRect(player.jumpshootingindex * 37, 0, 37, 50));
                }
                else {
                    player.sprite.setTextureRect(IntRect(player.jumpshootingindex * 37 + 37, 0, -37, 50));
                }*/
            }
            //cutting the sprite

        }
        else {



            player.jumpTimer += deltaTime;

            if (player.sprite.getTexture() != &player.jumpingAnimation)
                player.sprite.setTexture(player.jumpingAnimation);

            if (player.jumpTimer > 0.07f)
            {
                if (player.jumpIndex < 3)
                    player.jumpIndex++;

                if (player.facingRight)
                    player.sprite.setTextureRect(IntRect(player.jumpIndex * 29, 0, 29, 52));
                else
                    player.sprite.setTextureRect(IntRect(player.jumpIndex * 29 + 29, 0, -29, 52));

                player.jumpTimer = 0.f;
            }
        }
    }

}


//Smoke that appears behind the player when they're dashing
	void smokeupdate(Player & player, DashSmoke dashsmoke[15], float deltaTime) {
		for (int i = 0; i < player.smokenumber; i++) {
			if (dashsmoke[i].visible == true) {

				dashsmoke[i].display.setTexture(player.smokeDashAnimation);
				dashsmoke[i].display.setTextureRect(IntRect(dashsmoke[i].smokeIndex * 14, 0, 14, 31));
				dashsmoke[i].display.setScale(3.0f, 3.0f);


				dashsmoke[i].smokeDuration -= deltaTime;
				if (dashsmoke[i].smokeDuration <= 0) {
					dashsmoke[i].smokeIndex++;
					dashsmoke[i].smokeDuration = 0.02f;
				}
				if (dashsmoke[i].smokeIndex >= player.smokenumber) {
					dashsmoke[i].smokeIndex = 0;
					dashsmoke[i].visible = false;
					dashsmoke[i].smokeDuration = 0.02f;

				}

			}
		}
	}

    ////PLAYER SHOOTING ANIMATION

    //if (player.state == TELEPORT) {

    //    player.sprite.setTexture(player.teleport);//done
    //    //cutting the sprite
    //    player.sprite.setTextureRect(IntRect(player.shootingindex * 0, 0, 112, 115));
    //    player.shootingindex = (player.shootingindex + 1) % 13;

    //}
    
    //}
    //else if (player.state == RUNSHOOTING) {
    //    //linking player with sprite
    //    player.sprite.setTexture(player.shootingwhilerunning);
    //    //cutting the sprite
    //    player.sprite.setTextureRect(IntRect(player.shootingindex * 112, 0, 112, 115));
    //    player.shootingindex = (player.shootingindex + 1) % 10;
    //}
    //else if (player.state == DASHSHOOTING) {
    //    //linking player with the sprite
    //    player.sprite.setTexture(player.dashshooting);
    //    //cutting the sprite
    //    player.sprite.setTextureRect(IntRect(player.shootingindex * 160, 0, 160, 130));
    //    player.shootingindex = 2;

    //}

