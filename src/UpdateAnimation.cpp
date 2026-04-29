#include "UpdateAnimation.h"
#include <iostream>

using namespace sf;
using namespace std;
//NEVER SET STATES IN THIS FILE. STATES SHOULD ONLY BE MODIFIED IN PlayerMovement.cpp


void updateAnimation(Player& player, float deltaTime, bool& jumpKeyReleased) {
    if (player.isOnGround)
    {
        player.jumpIndex = 0;
        player.jumpTimer = 0.f;

        
        // Dashing (only while running on the ground)
        if (player.state == DASHING)
        {
            cout << "PLAYER DASHING IN ANIMATION" << endl;
            player.sprite.setTexture(player.dashrunAnimation);
            
            if (player.facingRight)
                player.sprite.setTextureRect(IntRect(0, 0, 41, 42));
            else
                player.sprite.setTextureRect(IntRect(41, 0, -41, 42));
        }
        // Running
        else if (player.state == RUNNING)
        {
            cout << "player is in running animation" << endl;
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