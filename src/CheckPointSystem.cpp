#include "CheckPointSystem.h"

//FUNCTIONS

//PLAYER SETUP
void setupPlayer(Player& player)
{
    player.texture.loadFromFile("player.png");
    player.sprite.setTexture(player.texture);
    //player.sprite.setPosition(100, 300);
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
    bool isDead = player.health <= 0;
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
        window.draw(checkpoints[i].shape);
    }

    window.draw(player.sprite);

    window.draw(healthText);

    window.draw(statusText);

    window.display();
}

//
//int main()
//{
//    RenderWindow window(VideoMode(800, 600), "Checkpoint System");
//    srand(time(0));
// 
// 
//    Player player;
//    setupPlayer(player);
//    float speed = 3.0f;
//    int healthAmount = 20;
//    int maxHealth = 100;
//
//   vector<Checkpoint>checkpoints;
// 
//   Vector2f lastCheckpointPos = player.sprite.getPosition();
//
//   //HEALTH DISPLAY
//   Font font;
//   font.loadFromFile("C:/Windows/Fonts/arial.ttf"); /////////check!!!!
//
//   Text healthText;
//   healthText.setFont(font);
//   healthText.setCharacterSize(20);
//   healthText.setFillColor(Color::White);
//
//   Clock clock;
// 
// vector<Vector2f> checkpointPositions = {
//    { 1400.f, 1550.f },
//    { 1900.f,  1550.f },
//    { 2500.f, 1350.f },
//    { 3000.f, 1450.f },
//    { 6000.f, 1300.f },
//    { 5700.f, 1450.f },
//    { 3900.f, 1400.f },
//    { 2300.f, 1450.f },
//    { 1800.f, 1350.f },
//    { 5500.f, 1450.f },
//    };
//
//   for (auto& pos : checkpointPositions)
//        checkpoints.push_back(createCheckpoint(pos.x, pos.y));
//   //GAME LOOP
//   while (window.isOpen())
//   {
//       float deltaTmie = clock.restart().asSeconds();
//       
//       Event event;
//       while (window.pollEvent(event))
//       {
//            if (event.type == Event::Closed)
//                window.close();
//       }
// 
// 
//        movePlayer(player, deltaTmie);
//
//        handleCheckpoints(player, checkpoints, lastCheckpointPos
//            , healthAmount, maxHealth);
//        respawn(player, lastCheckpointPos);
//
//        healthText.setString("HEALTH:" + to_string(player.health));
//        healthText.setPosition(10, 10);
//
//        drawAll(window, player, checkpoints, healthText);
//
//    }
//   return 0;
//}

