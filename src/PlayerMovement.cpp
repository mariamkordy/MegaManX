#include "PlayerMovement.h"
#include "Player.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;



//RESPONSIBLE FOR INPUT DEPENDENT MOTION AND STATE MODIFICATION





void playerMovement(Player& player, float deltaTime, DashSmoke dashsmoke[100], playerBullets Bullets[10])
{
    //if (player.shootingTimer > 0) {
    //    player.shootingTimer -= deltaTime;
    //}

 /*   if (player.isOnGround == true)
        cout << "" << endl;*/


    if (!player.isAlive || player.state == HURT) {
        if (player.state == HURT)player.velocity.x *= 0.95f; 
        else player.velocity.x = 0;
        player.hitbox.setPosition(player.sprite.getPosition());
        return;
    }


    float normalspeed = 300.f;
    float dashspeed = 1000.f;
    float currentspeed = normalspeed;
    //DASHING (INPUT AND UPDATE)



    if (player.state != DASHING) {
        player.smokeTimer = 0.f;
    }

    if (Keyboard::isKeyPressed(Keyboard::A) && (player.state == RUNNING || player.isOnGround) && !player.state == STANDING) {

        if (abs(player.velocity.x) > 1) {
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
        player.state = JUMPING;//

        //shooting?

        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            player.state = JUMPSHOOTING;
        }


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




    }

    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        player.velocity.x = currentspeed;
        player.facingRight = true;

        //shooting?
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            player.state = RUNSHOOTING;
        }

    }
    else {
        player.state = STANDING;
    }
    if (player.shootingTimer > 0) {
        player.shootingTimer -= deltaTime;
    }

    if (Keyboard::isKeyPressed(Keyboard::Space)) {

        if (player.shootingTimer <= 0.f) {
            for (int i = 0; i < 10; i++) {
                if (Bullets[i].active)continue;
                Bullets[i].active = true;


                if (player.facingRight) {
                    Bullets[i].velocity = Vector2f(1500.f, 0.f);
                    Bullets[i].position = player.sprite.getPosition() + Vector2f(80.f, 25.f);
                }

                else {
                    Bullets[i].velocity = Vector2f(-1500.f, 0.f);
                    Bullets[i].position = player.sprite.getPosition() + Vector2f(-80.f, 25.f);
                }
                Bullets[i].display.setPosition(Bullets[i].position);
                player.shootingTimer = 0.2f;
                break;

            }

        }



    }




    if (player.isDashing) {
        player.state = DASHING;
    }
    else if (!player.isOnGround) {
        player.state = Keyboard::isKeyPressed(Keyboard::Space) ? JUMPSHOOTING : JUMPING;
    }
    else if (abs(player.velocity.x) > 1.0f) {
        player.state = Keyboard::isKeyPressed(Keyboard::Space) ? RUNSHOOTING : RUNNING;
    }
    else {
        player.state = Keyboard::isKeyPressed(Keyboard::Space) ? IDLESHO : STANDING;
    }

    player.hitbox.setPosition(player.sprite.getPosition());

    //if (!player.isOnGround) {

    //    player.state = JUMPING;

    //}

    //else if (player.isDashing) {

    //    player.state = DASHING;

    //}

    //else if (abs(player.velocity.x) > 1.0f) { //moves fast enough for us to consider it to be running

    //    player.state = RUNNING;

    //}

    //else {

    //    player.state = STANDING;

    //}


}