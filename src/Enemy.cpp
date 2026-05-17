#include "Enemy.h"
#include "Player.h"


sf::Vector2f norm(sf::Vector2f v) {

    float l = std::sqrt(v.x * v.x + v.y * v.y);

    return (l == 0.f) ? sf::Vector2f(0, 0) : sf::Vector2f(v.x / l, v.y / l);
}

void loadLevel(std::vector<Enemy>& enemies, std::vector<FireTrap>& fires, EneTextures& eneTex) {
    enemies.clear(); fires.clear();

    //enemy type and position
    struct EData { int t; float x, y; };
    std::vector<EData> levelEnemies = {
        {1, 1043.9f, 1574.0f},
        {2,2043.9f, 1974.0f},
        {2,3755.2 , 1974},

        {1, 5297.81 , 1734},
        {1,  6613.1 , 3034},
        {3, 7393.73 , 2884},

        {1, 5297.81 , 1734},
        {1,  6613.1 , 3034},
        {3, 7393.73 , 2884},

        {3, 7993.35, 2884},
        {3, 8515.29 , 2799},
        {3, 9086.08 , 2799},
        {3, 9607.35 , 2874},
        { 3, 3645.59f, 1584.f },
        {3, 10109.9f, 2874.f},
        {3, 10510.3f, 2874.f},
        {3, 10905.f, 2014.f},
        {3, 11319.8f, 2874.f},
        {3, 9256.28f, 2369.f},
        {3, 9804.96f, 2294.f},
        {3, 10395.5f, 2294.f},
        {3, 3893.4f, 1584.f},
        {3, 10187.9f, 1594.f},
        {3, 9213.39f, 1294.f},

        {3, 9213.39f, 1294.f},
        {2, 12995.9f, 644.f},
        {1, 13748.4f, 504.f},
        {2, 14404.9f, 504.f},
        {1, 14828.6f, 854.f},
        {1, 17721.2f, 1434.f},
        {1, 18547.7f, 1434.f},
        {2, 21788.1f, 1734.f}

        /*, {1, 600.f, 460.f},
        {2, 16700.f, 1880.f},
        {3, 500.f, 460.f}, {3, 16750.f, 1880.f}*/
    };
    for (auto& d : levelEnemies) {
        Enemy e;
        e.type = d.t;
        e.pos = { d.x, d.y };
        e.startX = d.x;
        e.axeSprite.setTexture(eneTex.axe);
        e.sprite.setPosition(e.pos);
        if (e.type == 3) e.speed = 0;
        enemies.push_back(e);
    }
    //used for loops for consecutive fire
    std::vector<sf::Vector2f> levelFires;
    for (int x = 720; x <= 1330; x += 10) {
        levelFires.push_back(sf::Vector2f(x, 1770.f));
    }
    for (int x = 1535.17; x < 2105; x += 10) {
        levelFires.push_back(sf::Vector2f(x, 1770.f));
    }

    for (int x = 16601.4; x <= 17461.5; x += 10) {
        levelFires.push_back(sf::Vector2f(x, 1354));
    }

    for (int x = 17481.5; x <= 17930.6; x += 10) {
        levelFires.push_back(sf::Vector2f(x, 1554));
    }
    levelFires.push_back(sf::Vector2f(16631.4, 1214));

    for (auto& p : levelFires) {
        fires.push_back(FireTrap(p.x, p.y));
    }
}
void updateEnemies(std::vector<Enemy>& enemies, Player& player, float groundY, float dt) {
    sf::Vector2f playerPos = player.sprite.getPosition();
    for (auto& e : enemies) {
        if (!e.alive) continue; //لو ميت عديه
        //-------Dying Logic Animation---------
        if (e.dying) {
            e.animTimer += dt;
            if (e.animTimer >= 0.1f) {
                e.animTimer = 0;
                e.animFrame++;
            }
            if (e.animFrame >= 8) e.alive = false;
            continue;
        }
        float dist = std::abs(e.pos.x - playerPos.x);
        float fullDist = getDist(e.pos, playerPos);

        e.shootTimer = std::max(0.f, e.shootTimer - dt);
        e.isShooting = false;

        if (e.type == 3) {
            e.direction = (playerPos.x < e.pos.x) ? -1 : 1;
            e.throwCooldown -= dt;
            if (!e.throwing && !e.axeActive && e.throwCooldown <= 0 && fullDist < e.visionRange) {
                e.throwing = true;
                e.animFrame = 0;
                e.axeReleased = false;
            }
            if (e.throwing) {
                e.animTimer += dt;
                if (e.animTimer >= 0.1f) {
                    e.animTimer = 0;
                    e.animFrame++;
                }
                if (e.animFrame == 5 && !e.axeReleased) {
                    e.axeReleased = true;
                    e.axeActive = true;
                    e.axePos = e.pos + sf::Vector2f(e.direction * 20, 0); //الفاس يبدا يترمي من ايده 
                    e.axeDir = norm(playerPos - e.axePos); // خساب اتجاه الفاس للاعب
                }
                if (e.animFrame > 8) {
                    e.throwing = false;
                    e.throwCooldown = 2.0f;
                    e.animFrame = 0;
                }
            }
            //حركة الفاس في الجو
            if (e.axeActive) {
                e.axePos += e.axeDir * 450.f * dt; //الفاس يمشي بالسرعة دي 
                e.axeTimer += dt;
                if (e.axeTimer >= 0.08f) {
                    e.axeTimer = 0;
                    e.axeFrame = (e.axeFrame + 1) % 3; //Axe rotation
                }
                e.axeSprite.setPosition(e.axePos);
                if (player.sprite.getGlobalBounds().intersects(e.axeSprite.getGlobalBounds())) {
                    if (player.state != HURT && player.state != DEAD) {
                        player.health -= 15;
                        player.state = HURT;

                        // Player Knockback
                        float dir = (e.axePos.x > player.sprite.getPosition().x) ? -1.f : 1.f;
                        player.velocity.x = dir * 400.f;
                        player.velocity.y = -200.f;

                        e.axeActive = false; // الفأس يختفي لما يلمس اللاعب
                    }
                }
                if (std::abs(e.axePos.x - playerPos.x) > 1000.f) {
                    e.axeActive = false;
                }

            }
        }
        //types 1, 2    
        else {

            bool inSight = (fullDist < e.visionRange); //does the enemy detect the player?
            if (inSight) {
                e.direction = (playerPos.x > e.pos.x) ? 1 : -1; //يبص للاعب 

                if (e.type == 2) {
                    if (dist > 120.f) {
                        e.pos.x += e.direction * e.speed * dt;  // يقرب من اللاعب لحد ما المسافة ما بنهم تكون 120 عشان يضرب نار
                    }
                    else {
                        e.isShooting = true; // لو قرب يقف مكانه و يضرب نار
                    }
                }
                else {
                    e.isShooting = true; //type=1 يضرب علي طول اول ما يشوفه
                }

                //Shooting
                if (e.shootTimer <= 0) {
                    for (auto& b : e.bullets) {
                        if (b.active == false) {
                            b.active = true;
                            b.pos = e.pos + sf::Vector2f(e.direction * 15.f, -15.f); //المكان اللي بيطلع منو الطلقة
                            b.vel = norm(playerPos - b.pos) * 380.f; //سرعة الطلقة
                            b.damage = (e.type == 1) ? 5 : 10; //ال damage بتاع النوع 1 و 2
                            e.shootTimer = 1.5f; break;
                        }
                    }
                }
            }
            else {
                e.pos.x += e.direction * e.speed * dt; //patrol (FixedMove)
                if (std::abs(e.pos.x - e.startX) > e.patrolRange) e.direction *= -1; //يغير الاتجاه لو وصل لاخر ال patrolrange
            }

            //update bullet 
            for (auto& b : e.bullets) {
                if (b.active == true) {
                    b.pos += b.vel * dt;
                    if (getDist(b.pos, playerPos) < 25.f) {
                        player.health -= b.damage;
                        b.active = false;
                    }
                    if (std::abs(b.pos.x - playerPos.x) > 1000.f) {
                        b.active = false;
                    }
                }
            }

            e.animTimer += dt;
            if (e.animTimer >= 0.12f) {
                e.animTimer = 0;
                e.animFrame = (e.animFrame + 1) % 8;
            }
        }
        if (e.health <= 0) e.dying = true;
    }
}
void updateFires(std::vector<FireTrap>& fires, Player& player, float& fireDamageTimer, float dt) {
    sf::Vector2f playerPos = player.sprite.getPosition();
    fireDamageTimer += dt;
    bool hit = false;
    for (auto& f : fires) {
        f.drop.y += f.fallSpeed * dt;
        if (f.drop.y > f.start.y + f.fallDistance) {
            f.drop.y = f.start.y + f.startGap;
            f.frame = 1;
        }
        float prog = std::clamp((f.drop.y - f.start.y - f.startGap) / (f.fallDistance - f.startGap), 0.f, 1.f);

        float frameValue = prog * (FIRE_FRAMES - 2);
        f.frame = 1 + (int)frameValue;

        //Collision Detection 
        if (sf::FloatRect(f.drop.x - 15, f.drop.y - 15, 30, 30).intersects(player.sprite.getGlobalBounds())) hit = true;
    }
    if (hit && fireDamageTimer >= 0.5f) {
        player.health -= 5;
        fireDamageTimer = 0;
    }
}
void drawEnemies(sf::RenderWindow& window, std::vector<Enemy>& enemies, EneTextures& tex, sf::Vector2f playerPos) {
    for (auto& e : enemies) {
        if (!e.alive) continue;

        sf::Sprite s;
        if (e.type == 3) {
            s.setTexture(tex.enemy3);
            s.setTextureRect(sf::IntRect(e.animFrame * ENEMY3_W, 0, ENEMY3_W, ENEMY3_H));
            s.setOrigin(ENEMY3_W / 2.f, ENEMY3_H / 2.f);
            s.setScale((e.direction == 1) ? -ENEMY3_SCALE : ENEMY3_SCALE, ENEMY3_SCALE);
            s.setPosition(e.pos);
            window.draw(s);

            if (e.axeActive) {
                sf::Sprite ax(tex.axe);
                int fW = tex.axe.getSize().x / 3;
                ax.setTextureRect(sf::IntRect(e.axeFrame * fW, 0, fW, tex.axe.getSize().y));
                ax.setOrigin(fW / 2.f, tex.axe.getSize().y / 2.f);
                ax.setPosition(e.axePos);
                ax.setScale(AXE_SCALE, AXE_SCALE);
                window.draw(ax);
            }
        }
        else {
            s.setTexture(e.type == 1 ? tex.enemy1 : tex.enemy2);
            int row = (e.dying) ? 3 : ((e.isShooting || getDist(e.pos, playerPos) < e.visionRange) ? 2 : 0);
            s.setTextureRect(sf::IntRect(e.animFrame * ENEMY_W, row * ENEMY_H, ENEMY_W, ENEMY_H));
            s.setOrigin(ENEMY_W / 2.f, ENEMY_H / 2.f);
            s.setScale((e.direction == -1) ? -ENEMY_SCALE : ENEMY_SCALE, ENEMY_SCALE);
            s.setPosition(e.pos);
            window.draw(s);

            //yellow bullets
            for (auto& b : e.bullets) {
                if (b.active) {
                    sf::CircleShape bc(5.f);
                    bc.setFillColor(sf::Color::Yellow);
                    bc.setOrigin(5.f, 5.f);
                    bc.setPosition(b.pos);
                    window.draw(bc);
                }
            }
        }
    }
}
void drawFires(sf::RenderWindow& window, std::vector<FireTrap>& fires, sf::Texture& tex) {
    for (auto& f : fires) {
        sf::Sprite s(tex);
        s.setOrigin(FIRE_W / 2.f, FIRE_H / 2.f);
        s.setScale(f.scale, f.scale);
        s.setTextureRect({ 0,0,FIRE_W,FIRE_H });
        s.setPosition(f.start);
        window.draw(s);
        s.setTextureRect({ 0, f.frame * FIRE_H, FIRE_W, FIRE_H });
        s.setPosition(f.drop);
        window.draw(s);
    }
}