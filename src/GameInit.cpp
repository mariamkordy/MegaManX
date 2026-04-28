#include "GameInit.h"
#include <iostream>

using namespace std;
using namespace sf;

void Start(Player& player, View& view, RenderWindow& window,
           RectangleShape& ground, Background& background, TileMap& map)
{
    player.facingRight = true;
   
    player.isOnGround = false;
    //BACKGROUND
    if (!background.bgTexture.loadFromFile("assets/textures/bg.png"))
        cout << "BG FAILED\n";

    background.bgSprite.setTexture(background.bgTexture);
    background.bgSprite.setScale(3.f, 3.f);
    background.bgSprite.setPosition(-50, 5000);
    
    //PLAYER TEXTURES
    if (!player.jumpingAnimation.loadFromFile("assets/textures/jump.png"))
        cout << "JUMP FAILED\n";

    if (!player.dashrunAnimation.loadFromFile("assets/textures/dashrun.png"))
        cout << "DASHRUN FAILED\n";

    if (!player.runningAnimation.loadFromFile("assets/textures/running.png"))
        cout << "RUN FAILED\n";

    if (!player.standingAnimation.loadFromFile("assets/textures/standing.png"))
        cout << "STAND FAILED\n";

    if (!player.smokeDashAnimation.loadFromFile("assets/textures/dashsmoke_new_version.png"))
        cout << "SMOKE DASH FAILED\n";
    

    //MAP
    if (!loadTileMap(map, "assets/maps/MegaManXTest.tmx", "assets/maps/RedTileSet.png"))
    {
        cout << "Failed to load map\n";
    }

    player.jumpingAnimation.setSmooth(true);
    player.runningAnimation.setSmooth(true);
    player.standingAnimation.setSmooth(true);
    player.dashrunAnimation.setSmooth(true);

    player.sprite.setTexture(player.standingAnimation);
    player.sprite.setTextureRect(IntRect(0, 0, 36, 52));
    player.sprite.setScale(3.f, 3.f);
    player.sprite.setPosition(100.f, 150.f);

    ground.setSize(Vector2f(2000.f, 70.f));
    ground.setPosition(0.f, 1500.f);

    view.setSize(1680.f, 1050.f);
    view.zoom(0.8f);

    window.setFramerateLimit(60);
}

