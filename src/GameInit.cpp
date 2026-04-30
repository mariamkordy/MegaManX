#include "GameInit.h"
#include <iostream>

using namespace std;
using namespace sf;

void Start(Player& player, View& view, RenderWindow& window,
           vector<Ground>& grounds, vector<Wall>& walls, Background& background,Foreground& foreground, TileMap& map)
{
    Ground g;
    Wall w;
    player.facingRight = true;
   
   
    //BACKGROUND
    if (!background.bgTexture.loadFromFile("assets/textures/bg.png"))
        cout << "BG FAILED\n";
    if (!foreground.fgTexture.loadFromFile("assets/textures/fg.png"))
        cout << "FG FAILED\n";

    background.bgSprite.setTexture(background.bgTexture);
    foreground.fgSprite.setTexture(foreground.fgTexture);

    Vector2f target = Vector2f(window.getSize());
    Vector2f size = background.bgSprite.getLocalBounds().getSize();
    background.bgSprite.setScale(3.f, 4.5f);
    foreground.fgSprite.setScale(3.f, 4.5f);
    background.bgSprite.setPosition(-1210.f, -650.f);
    foreground.fgSprite.setPosition(-1210.f, -650.f);
    
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
    if (!loadTileMap(map, "assets/maps/Map.tmx", "assets/maps/RedTileSet.png", "assets/textures/fg.png"))
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
    player.sprite.setPosition(210.f, 1200.f);
    //GROUND BLOCKS
    
    //REMOVE THE COMMENT SIGN TO MAKE THE GROUND TRANSPARENT
    //g.rectangle.setFillColor(Color::Transparent);
    g.rectangle.setSize(Vector2f(260.f, 50.f));
    g.rectangle.setPosition(0.f, 1810.f);
    grounds.push_back(g);
    

    g.rectangle.setSize(Vector2f(250.f, 50.f));
    g.rectangle.setPosition(300.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(610.f, 50.f));
    g.rectangle.setPosition(700.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1650.f, 50.f));
    g.rectangle.setPosition(550.f, 2000.f);
    grounds.push_back(g);

    //CYAN FOR DEBUGGING PURPOSES.
    w.rectangle.setFillColor(Color::Cyan);
    //w.rectangle.setFillColor(Color::Transparent);
    w.rectangle.setSize(Vector2f(50.f, 400.f));
    w.rectangle.setPosition(250.f, 1600.f);
    walls.push_back(w);

    w.rectangle.setSize(Vector2f(50.f, 400.f));
    w.rectangle.setPosition(505.f, 1600.f);
    walls.push_back(w);

    w.rectangle.setSize(Vector2f(50.f, 200.f));
    w.rectangle.setPosition(705.f, 1600.f);
    walls.push_back(w);






    
    view.setSize(1680.f, 1050.f);
    view.zoom(0.8f);

    window.setFramerateLimit(60);
}

