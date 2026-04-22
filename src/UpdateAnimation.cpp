#include "UpdateAnimation.h"
#include <iostream>

void updateAnimation(Player& player, float deltaTime, bool& jumpKeyReleased)
{
	if (player.isOnGround)
	{
		player.animationLocked = false;
		player.jumpIndex = 0;
		player.jumpTimer = 0.f;
	}


	if (player.isDashing && player.isOnGround && player.isRunning) {
		player.sprite.setTexture(player.dashrunAnimation);
		player.animationLocked = true;
		if (player.facingRight) {
			player.sprite.setTextureRect(sf::IntRect(0, 0, 41, 42));
		}
		else {
			player.sprite.setTextureRect(sf::IntRect(41, 0, -41, 42));
		}
	}

	if (!player.isOnGround)
	{
		player.jumpTimer += deltaTime;
		player.animationLocked = true;
		player.isRunning = false;

		if (player.sprite.getTexture() != &player.jumpingAnimation)
			player.sprite.setTexture(player.jumpingAnimation);

		if (player.jumpTimer > 0.07f)
		{
			if (player.jumpIndex < 3)
				player.jumpIndex++;

			if (player.facingRight) {
				player.sprite.setTextureRect(sf::IntRect(player.jumpIndex * 29, 0, 29, 52));
			}
			else {
				player.sprite.setTextureRect(sf::IntRect(player.jumpIndex * 29 + 29, 0, -29, 52));
			}

			player.jumpTimer = 0.f;
		}
	}

	else if (player.isRunning && !player.animationLocked)
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

		if (player.facingRight) {
			player.sprite.setTextureRect(sf::IntRect(player.runIndex * 36, 0, 36, 52));
		}
		else {
			player.sprite.setTextureRect(sf::IntRect(player.runIndex * 36 + 36, 0, -36, 52));
		}
	}
	else if (!player.animationLocked)
	{
		if (player.sprite.getTexture() != &player.standingAnimation)
			player.sprite.setTexture(player.standingAnimation);

		if (!player.facingRight) {
			player.sprite.setTextureRect(sf::IntRect(36, 0, -36, 52));
		}
		else {
			player.sprite.setTextureRect(sf::IntRect(0, 0, 36, 52));
		}

		player.runIndex = 0;
	}
}

void smokeupdate(Player& player, DashSmoke dashsmoke[15], float deltaTime) {
	for (int i = 0; i < 15; i++) {
		if (dashsmoke[i].visible == true) {

			dashsmoke[i].display.setTexture(player.smokeDashAnimation);
			dashsmoke[i].display.setTextureRect(sf::IntRect(dashsmoke[i].smokeIndex * 14, 0, 14, 31));
			dashsmoke[i].display.setScale(3.0f, 3.0f);


			dashsmoke[i].smokeDuration -= deltaTime;
			if (dashsmoke[i].smokeDuration <= 0) {
				dashsmoke[i].smokeIndex++;
				dashsmoke[i].smokeDuration = 0.03f;
			}
			if (dashsmoke[i].smokeIndex >= 20) {
				dashsmoke[i].smokeIndex = 0;
				dashsmoke[i].visible = false;
				dashsmoke[i].smokeDuration = 0.03f;

			}

		}
	}

}