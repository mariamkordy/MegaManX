#include "UpdateAnimation.h"
#include <iostream>
#include"player.h"

using namespace sf;
using namespace std;
//NEVER SET STATES IN THIS FILE. STATES SHOULD ONLY BE MODIFIED IN PlayerMovement.cpp


void updateAnimation(Player& player, float deltaTime) {

    if (player.state == DYING) {
        player.runTimer += deltaTime; 
        if (player.runTimer > 0.15f) { 
            player.deathIndex = (player.deathIndex + 1) % 6;
            player.runTimer = 0.f;
        }
        player.sprite.setTexture(player.deathAnimation);
        player.sprite.setTextureRect(sf::IntRect(player.deathIndex * 32, 0, 32, 32));
    }
    else {
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

                int maxRunFrames = player.runningAnimation.getSize().x / 44;

                if (player.runTimer > 0.05f) {
                    player.runIndex++;
                    if (player.runIndex >= maxRunFrames)
                        player.runIndex = 0;
                    player.runTimer = 0.f;
                }

                if (player.facingRight)
                    player.sprite.setTextureRect(IntRect(player.runIndex * 44, 0, 44, 40));
                else
                    player.sprite.setTextureRect(IntRect(player.runIndex * 44 + 44, 0, -44, 40));
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
                    player.jumpshootingindex = (player.shootingindex + 1) % 7;

                    if (player.facingRight)
                        player.sprite.setTextureRect(IntRect(player.jumpshootingindex * 44, 0, 44, 51));
                    else
                        player.sprite.setTextureRect(IntRect((player.jumpshootingindex * 44) + 44, 0, -44, 51));
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
                        player.sprite.setTextureRect(IntRect(player.jumpIndex * 44, 0, 44, 51));
                    else
                        player.sprite.setTextureRect(IntRect(player.jumpIndex * 44 + 44, 0, -44, 51));

                    player.jumpTimer = 0.f;
                }
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
void updatePlayerBullets(Player & player, float deltaTime, playerBullets Bullets[10]) {
    for (int i = 0; i < 10; i++) {
        if (!Bullets[i].active)continue;

        //cout << "Bullet" << i << "moving atX:" << Bullets[i].position.x << endl;
        Bullets[i].position += Bullets[i].velocity * deltaTime;

        Bullets[i].display.setPosition(Bullets[i].position);
        Bullets[i].display.setTexture(player.playerBulletAnimation);

        if (Bullets[i].velocity.x > 0)
            Bullets[i].display.setTextureRect(IntRect(0, 0, 47, 37));
        else
            Bullets[i].display.setTextureRect(IntRect(47, 0, -47, 37));

        Bullets[i].display.setScale(2.0f, 2.0f);


        if (abs(Bullets[i].position.x - player.sprite.getPosition().x) > 1000) {
            Bullets[i].active = false;
        }
    }
    
}

//healtbar function
void HEALTHBAR(RenderWindow& window, Player& player, Texture& texture) {


    if (player.health >= 80 && player.health <= 100) {

        player.healthbarindex = 0;

    }
    else if (player.health >= 60 && player.health < 80) {

        player.healthbarindex = 1;
    }
    else if (player.health >= 40 && player.health < 60) {

        player.healthbarindex = 2;
    }
    else if (player.health >= 20 && player.health < 40) {

        player.healthbarindex = 3;
    }
    else {

        player.healthbarindex = 4;
    }
    Sprite healthbarsprite;
    healthbarsprite.setTexture(texture);
    int left = player.healthbarindex * 100;
    healthbarsprite.setTextureRect(IntRect(left, 0, 100, 200));
    healthbarsprite.setPosition(0, 50);
    /* healthbarsprite.setPosition(0, 50);*/
     //3a4an elsprite teb2a sabta 3ala el screen
    View healthview = window.getView();
    window.setView(window.getDefaultView());
    ///////
    window.draw(healthbarsprite);
    window.setView(healthview);
}