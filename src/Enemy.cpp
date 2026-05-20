#include "Enemy.h"
#include "Player.h"

sf::Vector2f norm(sf::Vector2f v) {
    float l = std::sqrt(v.x * v.x + v.y * v.y);
    return (l == 0.f) ? sf::Vector2f(0, 0) : sf::Vector2f(v.x / l, v.y / l);
}

void loadLevel(std::vector<Enemy>& enemies, std::vector<FireTrap>& fires, EneTextures& eneTex) {
    enemies.clear(); fires.clear();
    struct EData { int t; float x, y; };
    /*std::vector<EData> levelEnemies = {
        {1, 1043.9f, 1574.0f}, {2, 2043.9f, 1974.0f}, {2, 3755.2, 1974},
        {1, 5297.81, 1734}, {1, 6613.1, 3034}, {3, 7393.73, 2884},
        {3, 7993.35, 2884}, {3, 8515.29, 2799}, {3, 9086.08, 2799},
        {3, 9607.35, 2874}, {3, 3645.59f, 1584.f}, {3, 10109.9f, 2874.f},
        {3, 10510.3f, 2874.f}, {3, 10905.f, 2014.f}, {3, 11319.8f, 2874.f},
        {3, 9256.28f, 2369.f}, {3, 9804.96f, 2294.f}, {3, 10395.5f, 2294.f},
        {3, 3893.4f, 1584.f}, {3, 10187.9f, 1594.f}, {3, 9213.39f, 1294.f},
        {2, 12995.9f, 644.f}, {1, 13748.4f, 504.f}, {2, 14404.9f, 504.f},
        {1, 14828.6f, 854.f}, {1, 17721.2f, 1434.f}, {1, 18547.7f, 1434.f},
        {2, 21788.1f, 1734.f}
    };*/

    /*for (auto& d : levelEnemies) {
        Enemy e;
        e.type = d.t;
        e.pos = { d.x, d.y };
        e.startX = d.x;
        e.sprite.setPosition(e.pos);
        if (e.type == 3) e.speed = 0;
        if (e.type == 3) e.direction = 1;
        enemies.push_back(e);
    }*/

    std::vector<sf::Vector2f> levelFires;
    for (int x = 720; x <= 1330; x += 10) levelFires.push_back(sf::Vector2f(x, 1770.f));
    for (int x = 1535.17; x < 2105; x += 10) levelFires.push_back(sf::Vector2f(x, 1770.f));
    for (int x = 16601.4; x <= 17461.5; x += 10) levelFires.push_back(sf::Vector2f(x, 1354));
    for (int x = 17481.5; x <= 17930.6; x += 10) levelFires.push_back(sf::Vector2f(x, 1554));
    levelFires.push_back(sf::Vector2f(16631.4, 1214));

    for (auto& p : levelFires) fires.push_back(FireTrap(p.x, p.y));
}

void updateEnemies(std::vector<Enemy>& enemies, Player& player, float dt) {
    sf::Vector2f playerPos = player.sprite.getPosition();
    for (auto& e : enemies) {
        if (!e.alive) continue;

        if (e.dying) {
            e.animTimer += dt;
            if (e.animTimer >= 0.1f) { e.animTimer = 0; e.animFrame++; }
            if (e.animFrame >= 8) e.alive = false;
            continue;
        }

        float fullDist = std::sqrt(std::pow(e.pos.x - playerPos.x, 2) + std::pow(e.pos.y - playerPos.y, 2));
        e.shootTimer = std::max(0.f, e.shootTimer - dt);
        e.isShooting = false;

        bool sameY = (std::abs(e.pos.y - playerPos.y) < 300.f);
        bool inSight = (fullDist < e.visionRange) && (e.type == 3 ? true : sameY);

        if (inSight) {
            e.direction = (playerPos.x > e.pos.x) ? 1 : -1;

            if (e.type == 2) {
                if (std::abs(e.pos.x - playerPos.x) > 200.f) {
                    e.pos.x += e.direction * e.speed * dt;
                } else {
                    e.isShooting = true;
                }
            }
            else if (e.type == 1) {
                e.isShooting = true;
            }
            else if (e.type == 3) {
                e.direction = (playerPos.x > e.pos.x) ? 1 : -1;
                e.isShooting = true;
                if (e.shootTimer <= 0) {
                    for (auto& a : e.axes) {
                        if (!a.active) {
                            a.active = true;
                            a.pos = e.pos + sf::Vector2f(e.direction * 20.f, -30.f);
                            a.vel = sf::Vector2f(e.direction * 300.f, -400.f);
                            a.damage = 15;
                            e.shootTimer = 2.0f;
                            break;
                        }
                    }
                }
            }

            if (e.shootTimer <= 0 && e.type != 3) {
                for (auto& b : e.bullets) {
                    if (!b.active) {
                        b.active = true;
                        b.pos = e.pos + sf::Vector2f(e.direction * 20.f, -10.f);
                        b.vel = norm(playerPos - b.pos) * 400.f;
                        b.damage = (e.type == 1) ? 5 : 15;
                        e.shootTimer = 1.5f;
                        break;
                    }
                }
            }
        } else if (e.type != 3) {
            if (e.eState == 0) {
                e.pos.x += e.direction * e.speed * dt;
                if (std::abs(e.pos.x - e.startX) > e.patrolRange) e.direction *= -1;
            }
        }

        if (e.type == 3) {
            e.direction = (playerPos.x > e.pos.x) ? 1 : -1;
        }

        for (auto& b : e.bullets) {
            if (b.active) {
                b.pos += b.vel * dt;
                if (std::abs(b.pos.x - playerPos.x) < 25.f && std::abs(b.pos.y - playerPos.y) < 50.f) {
                    if (player.state != HURT && player.state != DEAD) {
                        player.health -= b.damage;
                        player.state = HURT;
                        b.active = false;
                    }
                }
                if (std::abs(b.pos.x - e.pos.x) > 500.f || b.pos.y < 0 || b.pos.x > 25000)
                    b.active = false;
            }
        }

        for (auto& a : e.axes) {
            if (a.active) {
                a.pos += a.vel * dt;
                a.vel.y += 800.f * dt;
                a.animTimer += dt;
                if (a.animTimer >= 0.08f) {
                    a.animTimer = 0;
                    a.frame = (a.frame + 1) % AXE_FRAMES;
                }
                if (std::abs(a.pos.x - playerPos.x) < 50.f && std::abs(a.pos.y - playerPos.y) < 80.f) {
                    if (player.state != HURT && player.state != DEAD) {
                        player.health -= a.damage;
                        player.state = HURT;
                        a.active = false;
                    }
                }
                if (a.pos.y > 5000.f || a.pos.x < 0 || a.pos.x > 25000.f)
                    a.active = false;
            }
        }

        e.animTimer += dt;
        if (e.animTimer >= 0.15f) {
            e.animTimer = 0;
            if (e.type == 3) e.animFrame = (e.animFrame + 1) % 2;
            else e.animFrame = (e.animFrame + 1) % 6;
        }

        if (e.eState == 1) {
            e.hurtTimer -= dt;
            if (e.hurtTimer <= 0) e.eState = 0;
        }

        if (e.health <= 0) e.dying = true;
    }
}

void drawEnemies(sf::RenderWindow& window, std::vector<Enemy>& enemies, EneTextures& tex, Player& player) {
    for (auto& e : enemies) {
        if (!e.alive) continue;

        sf::Sprite s;
        if (e.type == 3) s.setTexture(tex.enemy3);
        else s.setTexture(e.type == 1 ? tex.enemy1 : tex.enemy2);

        int row = (e.dying) ? 3 : (e.isShooting ? 2 : 0);
        int useRow = (e.type == 3) ? 0 : row;
        float ew = (e.type == 3) ? ENEMY3_W : ENEMY_W;
        float eh = (e.type == 3) ? ENEMY3_H : ENEMY_H;
        float es = (e.type == 3) ? ENEMY3_SCALE : ENEMY_SCALE;

        s.setTextureRect(sf::IntRect(e.animFrame * ew, useRow * eh, ew, eh));
        s.setOrigin(ew / 2.f, eh * 0.5f);
        s.setScale((e.direction == -1) ? -es : es, es);
        s.setPosition(e.pos);
        window.draw(s);

        // ======= رسم الـ bullet بـ texture منفصلة =======
          for (auto& b : e.bullets) {
            if (b.active) {
                sf::Sprite bulletSprite;
                bulletSprite.setTexture(tex.enemyBullet);
                bulletSprite.setOrigin(
                    tex.enemyBullet.getSize().x / 2.f,
                    tex.enemyBullet.getSize().y / 2.f
                );
                bulletSprite.setScale(
                    (b.vel.x > 0) ? 4.f : -4.f, 4.f
                );
                bulletSprite.setPosition(b.pos);
                if (tex.enemyBullet.getSize().x == 0)
                    printf("ERROR: enemyBullet texture not loaded!\n");
                window.draw(bulletSprite);
            }
        }

        // ======= رسم الـ axe =======
        for (auto& a : e.axes) {
            if (a.active) {
                sf::Sprite axeSprite;
                axeSprite.setTexture(tex.axe);
                axeSprite.setTextureRect(sf::IntRect(a.frame * AXE_W, 0, AXE_W, AXE_H));
                axeSprite.setOrigin(AXE_W / 2.f, AXE_H / 2.f);
                axeSprite.setPosition(a.pos);
                axeSprite.setScale(AXE_SCALE, AXE_SCALE);
                window.draw(axeSprite);
            }
        }
    }
}

void updateFires(std::vector<FireTrap>& fires, Player& player, float& fireDamageTimer, float dt) {
    sf::Vector2f playerPos = player.sprite.getPosition();
    fireDamageTimer = std::max(0.f, fireDamageTimer - dt);

    for (auto& f : fires) {
        f.drop.y += f.fallSpeed * dt;
        if (f.drop.y - f.start.y >= f.fallDistance) f.drop.y = f.start.y + f.startGap;

        if (std::abs(f.drop.x - playerPos.x) < 20.f && std::abs(f.drop.y - playerPos.y) < 30.f) {
            if (fireDamageTimer <= 0.f && player.state != DEAD) {
                player.health -= 10;
                player.state = HURT;
                fireDamageTimer = 1.0f;
            }
        }
    }
}

void drawFires(sf::RenderWindow& window, std::vector<FireTrap>& fires, sf::Texture& fireTexture) {
    for (auto& f : fires) {
        sf::Sprite s;
        s.setTexture(fireTexture);
        s.setTextureRect(sf::IntRect(f.frame * FIRE_W, 0, FIRE_W, FIRE_H));
        s.setScale(std::abs(f.scale), std::abs(f.scale));
        s.setPosition(f.drop);
        window.draw(s);
    }
}