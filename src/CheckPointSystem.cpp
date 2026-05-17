#include "CheckPointSystem.h"

//FUNCTIONS

//PLAYER SETUP
void setupPlayer(Player& player)
{
    player.texture.loadFromFile("player.png");
    player.sprite.setTexture(player.texture);
    player.sprite.setPosition(20806, 2004);
    player.speed = 200.0f;
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
    cp.shape.setSize(Vector2f(30, 60));
    cp.shape.setPosition(x, y);
    cp.shape.setFillColor(Color::Red);
    cp.activated = false;
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
void applyDamange(Player& player, int damage)
{
    player.health -= damage;
    if (player.health < 0)
    {
        player.health = 0;
    }
}

//COLLISION+ACTIVATION+HEALTHAMOUNT
void handleCheckpoints(Player& player, vector<Checkpoint>& checkpoints,
    Vector2f& lastCheckpointPos, int healthAmount, int maxHealth)
{
    for (int i = 0; i < checkpoints.size(); i++)
    {
        if (player.sprite.getGlobalBounds().intersects(checkpoints[i].shape.getGlobalBounds()))
        {
            if (!checkpoints[i].activated)
            {
                checkpoints[i].activated = true;
                checkpoints[i].shape.setFillColor(Color::Green);
                lastCheckpointPos = checkpoints[i].shape.getPosition();
                
                
                player.health += healthAmount;
                if (player.health > maxHealth)
                {
                    player.health = maxHealth;
                }
            }
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
        //player.sprite.setTexture(player.standingAnimation);
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
        window.draw(checkpoints[i].shape);
    }

    window.draw(player.sprite);

    window.draw(healthText);

    window.draw(statusText);

    window.display();
}

