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

    g.rectangle.setSize(Vector2f(240.f, 50.f));//a
    g.rectangle.setPosition(0.f, 1810.f);
    grounds.push_back(g);
    

    g.rectangle.setSize(Vector2f(250.f, 50.f));//b
    g.rectangle.setPosition(300.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(610.f, 50.f));//d
    g.rectangle.setPosition(700.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1650.f, 50.f));//c
    g.rectangle.setPosition(550.f, 2000.f);
    grounds.push_back(g);



    g.rectangle.setSize(Vector2f(550.f, 50.f));//e
    g.rectangle.setPosition(1540.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(250.f, 50.f));//f
    g.rectangle.setPosition(2300.f, 1600.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(250.f, 50.f));//g
    g.rectangle.setPosition(2600.f, 1900.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1850.f, 50.f));//h
    g.rectangle.setPosition(2850.f, 2000.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(300.f, 50.f));//k
    g.rectangle.setPosition(4750.f, 1900.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(80.f, 50.f));//i
    g.rectangle.setPosition(3070.f, 1750.f);
    grounds.push_back(g);



    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3150.f, 1750.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3160.f, 1746.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3170.f, 1743.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3180.f, 1739.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3190.f, 1736.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3200.f, 1732.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3210.f, 1729.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3220.f, 1725.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3230.f, 1722.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3240.f, 1718.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3250.f, 1715.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3260.f, 1711.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3270.f, 1708.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3280.f, 1704.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3290.f, 1701.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3300.f, 1697.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3310.f, 1694.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3320.f, 1690.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3330.f, 1687.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3340.f, 1683.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3350.f, 1680.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3360.f, 1676.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3370.f, 1673.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3380.f, 1669.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3390.f, 1666.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3400.f, 1662.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3410.f, 1659.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3420.f, 1655.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3430.f, 1652.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3440.f, 1648.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3450.f, 1645.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3460.f, 1641.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3470.f, 1638.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3480.f, 1634.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3490.f, 1631.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3500.f, 1627.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3510.f, 1624.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3520.f, 1620.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3530.f, 1617.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3540.f, 1613.5f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(10.f, 50.f));
    g.rectangle.setPosition(3550.f, 1610.f);
    grounds.push_back(g);
    //g.rectangle.setSize(Vector2f(10.f, 50.f));
    //g.rectangle.setPosition(3560.f, 1606.5f);
    //grounds.push_back(g);
    //g.rectangle.setSize(Vector2f(10.f, 50.f));
    //g.rectangle.setPosition(3570.f, 1603.f);
    //grounds.push_back(g);
    //g.rectangle.setSize(Vector2f(10.f, 50.f));
    //g.rectangle.setPosition(3580.f, 1599.5f);
    //grounds.push_back(g);
    //g.rectangle.setSize(Vector2f(10.f, 50.f));
    //g.rectangle.setPosition(3590.f, 1596.f);
    //grounds.push_back(g);



    g.rectangle.setSize(Vector2f(180.f, 50.f));//j
    g.rectangle.setPosition(3550.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(200.f, 50.f));//m
    g.rectangle.setPosition(3900.f, 1600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(80.f, 50.f));//l
    g.rectangle.setPosition(4500.f, 1750.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(550.f, 50.f));//n
    g.rectangle.setPosition(5090.f, 1750.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1400.f, 50.f));//o
    g.rectangle.setPosition(5700.f, 3050.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(4400.f, 50.f));//r
    g.rectangle.setPosition(7100.f, 3200.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1050.f, 50.f));//q
    g.rectangle.setPosition(7200.f, 2890.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(900.f, 50.f));//s
    g.rectangle.setPosition(8400.f, 2815.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(830.f, 50.f));//u
    g.rectangle.setPosition(9450.f, 2890.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1050.f, 50.f));//z
    g.rectangle.setPosition(10450.f, 2890.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(380.f, 50.f));//t
    g.rectangle.setPosition(9115.f, 2385.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(860.f, 50.f));//v
    g.rectangle.setPosition(9690.f, 2310.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(860.f, 50.f));
    g.rectangle.setPosition(9690.f, 2610.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(570.f, 50.f));//y
    g.rectangle.setPosition(10650.f, 2030.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(550.f, 50.f));
    g.rectangle.setPosition(11000.f, 1900.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(860.f, 50.f));//x
    g.rectangle.setPosition(9790.f, 1610.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(680.f, 50.f));//w
    g.rectangle.setPosition(8920.f, 1310.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(570.f, 50.f));//aa
    g.rectangle.setPosition(11515.f, 1730.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(570.f, 50.f));
    g.rectangle.setPosition(11550.f, 1480.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(570.f, 50.f));
    g.rectangle.setPosition(11550.f, 1200.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(570.f, 50.f));
    g.rectangle.setPosition(11550.f, 1000.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(570.f, 50.f));
    g.rectangle.setPosition(11550.f, 700.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(285.f, 50.f));//ab
    g.rectangle.setPosition(12090.f, 440.f);
    grounds.push_back(g);



    g.rectangle.setSize(Vector2f(280.f, 50.f));//ac
    g.rectangle.setPosition(12380.f, 600.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(2840.f, 50.f));//ae
    g.rectangle.setPosition(12660.f, 870.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(560.f, 50.f));//ad
    g.rectangle.setPosition(12770.f, 660.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(650.f, 50.f));//af
    g.rectangle.setPosition(13440.f, 520.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(550.f, 50.f));//ag
    g.rectangle.setPosition(14210.f, 520.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(460.f, 50.f));//ai
    g.rectangle.setPosition(14980.f, 660.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(380.f, 50.f));//aj
    g.rectangle.setPosition(15550.f, 580.f);
    grounds.push_back(g);



    g.rectangle.setSize(Vector2f(550.f, 50.f));//ak
    g.rectangle.setPosition(15950.f, 1880.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(1950.f, 50.f));//ah
    g.rectangle.setPosition(16500.f, 2020.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(200.f, 50.f));//al
    g.rectangle.setPosition(16600.f, 1880.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(500.f, 50.f));//am
    g.rectangle.setPosition(16810.f, 1750.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(200.f, 50.f));//an
    g.rectangle.setPosition(17350.f, 1950.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(300.f, 50.f));//ao
    g.rectangle.setPosition(17730.f, 1950.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(240.f, 50.f));//as
    g.rectangle.setPosition(17510.f, 1450.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(460.f, 50.f));//at
    g.rectangle.setPosition(18250.f, 1450.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(80.f, 50.f));//as``
    g.rectangle.setPosition(17810.f, 1450.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(190.f, 50.f));//ap
    g.rectangle.setPosition(18050.f, 1740.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(860.f, 50.f));//aq
    g.rectangle.setPosition(16610.f, 1230.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(100.f, 50.f));//au
    g.rectangle.setPosition(18710.f, 1520.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(100.f, 50.f));//au``
    g.rectangle.setPosition(18860.f, 1520.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(420.f, 50.f));//av
    g.rectangle.setPosition(18970.f, 1380.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(100.f, 50.f));//ax
    g.rectangle.setPosition(18710.f, 1750.f);
    grounds.push_back(g);   
    
    g.rectangle.setSize(Vector2f(2500.f, 50.f));//a0
    g.rectangle.setPosition(18810.f, 2020.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(310.f, 50.f));//ay
    g.rectangle.setPosition(18810.f, 1880.f);
    grounds.push_back(g);


    g.rectangle.setSize(Vector2f(440.f, 50.f));//aaa
    g.rectangle.setPosition(19400.f, 1880.f);
    grounds.push_back(g);

    g.rectangle.setSize(Vector2f(400.f, 50.f));//aac
    g.rectangle.setPosition(20020.f, 1880.f);
    grounds.push_back(g);

    //---------------------WALLS---------------------
    //CYAN FOR DEBUGGING PURPOSES. REMOVE THE COMMENT SIGN ON THE FOLLOWING LINE TO MAKE WALLS TRANSPARENT
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

