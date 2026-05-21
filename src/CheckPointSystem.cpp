#include "CheckPointSystem.h"
#include<iostream>
#include <SFML/Audio.hpp>

//FUNCTIONS

//PLAYER SETUP
void setupPlayer(Player& player)
{
    player.texture.loadFromFile("player.png");
    player.sprite.setTexture(player.texture);
    //player.sprite.setPosition(100, 200);
    player.speed = 300.0f;
    player.health = 100;
    player.frame = 0;
    player.animationTimer = 0;
    player.animationSpeed = 0.1f;
    player.isOnWall = false;
    player.sprite.setTextureRect(IntRect(0, 0, 32, 32));

}


//CHECKPOINT SETUP
Checkpoint createCheckpoint(float x, float y)
{
    Checkpoint cp;

    if (!cp.idlePosition.loadFromFile("assets/textures/checkpoint idle state.png")) {
        cout << "CHECKPOINT IDLE FAILED\n";
    }

    if (!cp.activatingPosition.loadFromFile("assets/textures/checkpoint activating 3.png")) {
        cout << "CHECKPOINT USED FAILED\n";
    }

    if (!cp.usedPosition.loadFromFile("assets/textures/checkpint used state.png")) {
        cout << "CHECKPOINT USED FAILED\n";
    }
    
    cp.usedPosition.setSmooth(true);
    cp.idlePosition.setSmooth(true);
    cp.activatingPosition.setSmooth(true);
    
    cp.sprite.setTexture(cp.idlePosition);
    cp.sprite.setPosition(x, y);

    cp.sprite.setTextureRect(sf::IntRect(0, 0, 59, 110));
    cp.sprite.scale(2.5, 2.5);
    

    // 3. Create a collision zone right at the bottom center pad
    cp.bounds = sf::FloatRect(x + 16, y + 48, 32, 48);

    // 4. Initial animation states
    cp.pointstate = idle;
    cp.frame = 0;
    cp.animationtimer = 0.0f;
    cp.activationtotaltime = 0.0f;
    cp.animationSpeed = 0.05f; 

    return cp;

}

//PLAYER MOVEMENT
void movePlayer(Player& player, float deltaTime)
{
    bool moving = false;
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        player.sprite.move(-player.speed*deltaTime, 0);
        moving = true;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        player.sprite.move(player.speed * deltaTime, 0);
        moving = true;
    }

    player.animationTimer += deltaTime;
    if (moving)
    {
        if (player.animationTimer >= player.animationSpeed)
        {
            player.animationTimer = 0;
            player.frame++;

            if (player.frame > 3)
            {
                player.frame = 0;
            }

            player.sprite.setTextureRect(IntRect(player.frame * 32, 0, 32, 32));
        }
    }

    else
    {
        player.sprite.setTextureRect(IntRect(0, 0, 32, 32));
    }
    
}

//DAMAGE
void applyDamage(Player& player, int damage)
{
    player.health -= damage;
    if (player.health < 0)
    {
        player.health = 0;
    }
}

void handleCheckpoints(Player& player, vector<Checkpoint>& checkpoints,
    Vector2f& lastCheckpointPos, int healthAmount, int maxHealth, float deltaTime, sf::Sound& cpSound)
{
    for (int i = 0; i < checkpoints.size(); i++)
    {

        if (checkpoints[i].pointstate == idle)
        {

            checkpoints[i].animationtimer += deltaTime;

            if (checkpoints[i].animationtimer >= checkpoints[i].animationSpeed)
            {
                checkpoints[i].animationtimer = 0.0f;
                checkpoints[i].frame++;

                if (checkpoints[i].frame > 2)
                {
                    checkpoints[i].frame = 0;
                }

                
                checkpoints[i].sprite.setTexture(checkpoints[i].idlePosition);
                checkpoints[i].sprite.setTextureRect(sf::IntRect(checkpoints[i].frame * 59, 0, 59, 110));
            }

            sf::Vector2f pos = checkpoints[i].sprite.getPosition();

            
            sf::FloatRect preciseFeetZone(pos.x + 90, pos.y + 200, 67, 75);

            
            if (player.sprite.getGlobalBounds().intersects(preciseFeetZone))
            {
                
                checkpoints[i].pointstate = activating;

                checkpoints[i].frame = 0;
                checkpoints[i].animationtimer = 0.f;

                checkpoints[i].sprite.setTexture(checkpoints[i].activatingPosition);
                
                player.speed += 200;


                lastCheckpointPos = checkpoints[i].sprite.getPosition();
                player.health = maxHealth;
                if (player.health > maxHealth)
                {
                    player.health = maxHealth;
                }

                // --- NEW: START LOOPING SOUND ---
                cpSound.setLoop(true);
                cpSound.play();


            }
        }

        if (checkpoints[i].pointstate == activating)
        {
          
            checkpoints[i].activationtotaltime += deltaTime;


            if (checkpoints[i].activationtotaltime >= 3.0f)
            {
                checkpoints[i].pointstate = used;
                checkpoints[i].frame = 0;
                checkpoints[i].sprite.setTexture(checkpoints[i].usedPosition); 

                lastCheckpointPos = checkpoints[i].sprite.getPosition();
                player.health += healthAmount;
                if (player.health > maxHealth) player.health = maxHealth;
                // --- NEW: STOP SOUND ---
                cpSound.setLoop(false);
                cpSound.stop();
            }
            else
            {

                checkpoints[i].animationtimer += deltaTime;

                if (checkpoints[i].animationtimer >= checkpoints[i].animationSpeed)
                {
                    checkpoints[i].animationtimer = 0.f;
                    checkpoints[i].frame++;

                    if (checkpoints[i].frame > 3)
                    {
                        checkpoints[i].frame = 0;
                    }

                    checkpoints[i].sprite.setTextureRect(sf::IntRect(checkpoints[i].frame * 59, 0, 59, 110));
                }
            }
        }



        if (checkpoints[i].pointstate == used)
        {

            checkpoints[i].sprite.setTextureRect(sf::IntRect(0, 0, 59, 110));
        }

    }
}



//RESPAWN
void respawn(Player& player, Vector2f lastCheckpointPos)
{
    bool isDead = (player.state == DYING) && (player.alive == false);
    bool manualReset = Keyboard::isKeyPressed(Keyboard::R);
   
    if (isDead || manualReset)
    {
        player.sprite.setPosition(lastCheckpointPos);
        player.health = 100;
        player.frame = 0;
        player.animationTimer = 0;

        player.sprite.setTextureRect(IntRect(0, 0, 32, 32));
    
    }

}


//DRAW
void drawAll(RenderWindow& window, Player& player,
    vector<Checkpoint>& checkpoints, Text& healthText,Text& statusText)
{
    window.clear();
    for (int i = 0; i < checkpoints.size(); i++)
    {
        window.draw(checkpoints[i].sprite);
    }

    window.draw(player.sprite);

    window.draw(healthText);

    window.draw(statusText);

    window.display();
}

