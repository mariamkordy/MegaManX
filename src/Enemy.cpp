#include "Enemy.h"

//هنا بنعمل norm=1 عشان نقدر نتحكم في السرعة بتاعة اي حاجة
sf::Vector2f norm(sf::Vector2f v) {
    //بنجيب الطول
    float l = std::sqrt(v.x * v.x + v.y * v.y);
    //هنا بنخلي طوله 1
    return (l == 0.f) ? sf::Vector2f(0, 0) : sf::Vector2f(v.x / l, v.y / l);
}

void loadLevel(std::vector<Enemy>& enemies, std::vector<FireTrap>& fires) {
    //هنا بنمسح اي enemy , fire عشان لو هنعمل level تاني 
    enemies.clear(); fires.clear();

    //هنا بنكتب ال type , position بتاع ال enemy
    struct EData { int t; float x, y; };
    std::vector<EData> levelEnemies = {
        {1, 16420.9f,1824.0f}, {1, 600.f, 460.f},
        {2, 16700.f, 1880.f},
        {3, 500.f, 460.f}, {3, 16750.f, 1880.f}
    };
    //هنا بقي بنحول الارقام اللي فوق ل enemy حقيقي
    for (auto& d : levelEnemies) {
        Enemy e;
        e.type = d.t;
        e.pos = { d.x, d.y };
        e.startX = d.x;
        e.sprite.setPosition(e.pos);
        if (e.type == 3) e.speed = 0;
        enemies.push_back(e);
    }
    //هنا نفس الكلام اللي فوق بس لل fire
    std::vector<sf::Vector2f> levelFires = {
        {400.f, 40.f}, {800.f, 40.f},
        {1100.f, 40.f} };
    for (auto& p : levelFires) {
        fires.push_back(FireTrap(p.x, p.y));
    }
}
//هنا بقي دي ال function الاساسيه لل enemy  ,  و كمان هنا فيه اسماء للاعب فغيروها للاسماء اللي انتو عملنها
void updateEnemies(std::vector<Enemy>& enemies, sf::Vector2f playerPos, float& playerHealth, float groundY, float dt) {
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

        //-------Gravity , Vertical Move-------------
        if (!e.grounded) e.vel.y += 600.f * dt; // بسرع ال enemy و هو نازل من فوق
        e.pos.y += e.vel.y * dt; // بنحدد مكانه 
        //----Ground collision-------
        if (e.pos.y + 40.f >= groundY) {
            e.pos.y = groundY - 40.f; //بنثبت ال enemy فوق الارض ب 40 بكسل 
            e.vel.y = 0;
            e.grounded = true;
        }
        //المسافة بين ال enemy and player 
        float dist = std::abs(e.pos.x - playerPos.x);
        float fullDist = getDist(e.pos, playerPos);

        e.shootTimer = std::max(0.f, e.shootTimer - dt); //عشان الوقت ميبقاش بال -ve
        e.isShooting = false;

        if (e.type == 3) {
            e.direction = (playerPos.x < e.pos.x) ? -1 : 1; // هنا عشان يبص ناحية اللاعب
            e.throwCooldown -= dt; // بنقلل الوقت اللي هيرمي فيه الفاس 
            // الشروط عشان يبدا يرمي الفاس
            if (!e.throwing && !e.axeActive && e.throwCooldown <= 0 && fullDist < e.visionRange) {
                e.throwing = true;
                e.animFrame = 0;
                e.axeReleased = false;
            }
            if (e.throwing) {
                //ال Animation بتاع رمي الفاس
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
                    e.axeFrame = (e.axeFrame + 1) % 3; //دوران الفاس 
                }
                //لو الفاس لمس اللاعب , هنا فيه اسامي للplayer غيريها للاسم اللي انت عملاه
                if (getDist(e.axePos, playerPos) < 30.f) {
                    playerHealth -= 15;
                    e.axeActive = false;
                }
                //لو الفاس خرج بره حدود الشاشة يختفي
                if (e.axePos.x < -200 || e.axePos.x > 3000) e.axeActive = false;
            }
        }
        //type1 ,2    
        else {

            bool inSight = (fullDist < e.visionRange); //هل ال enemy شايف اللاعب
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

                //Logic ضرب النار
                if (e.shootTimer <= 0) {
                    for (auto& b : e.bullets) {
                        if (b.active == false) {
                            b.active = true; //لو الطلقة مش active يشغلها
                            b.pos = e.pos + sf::Vector2f(e.direction * 15.f, -15.f); //المكان اللي بيطلع منو الطلقة
                            b.vel = norm(playerPos - b.pos) * 380.f; //سرعة الطلقة
                            b.damage = (e.type == 1) ? 5 : 10; //ال damage بتاع النوع 1 و 2
                            e.shootTimer = 1.5f; break; //يستني 1.5 ثانية عشان يضرب تاني 
                        }
                    }
                }
            }
            else {
                e.pos.x += e.direction * e.speed * dt; //ال patrol (FixedMove)
                if (std::abs(e.pos.x - e.startX) > e.patrolRange) e.direction *= -1; //يغير الاتجاه لو وصل لاخر ال patrolrange
            }

            //update bullet 
            for (auto& b : e.bullets) {
                if (b.active == true) {
                    b.pos += b.vel * dt; //مكان الطلقة 
                    if (getDist(b.pos, playerPos) < 25.f) { //لو الطلقة لمست اللاعب , فيه اسماء لل player غيريها للاسماء اللي اللي انتو عملنها
                        playerHealth -= b.damage;
                        b.active = false;
                    }
                    if (b.pos.x < -100 || b.pos.x > 3000) b.active = false; //يشيل الطلقة لو خرجت بره الشاشة 
                }
            }
            //ال animation بتاع type 1,2
            e.animTimer += dt;
            if (e.animTimer >= 0.12f) {
                e.animTimer = 0;
                e.animFrame = (e.animFrame + 1) % 8;
            }
        }
        if (e.health <= 0) e.dying = true; //يموت لو ال health بقي 0
    }
}
//فيه اسامي لل player
void updateFires(std::vector<FireTrap>& fires, sf::Vector2f playerPos, float& playerHealth, float& fireDamageTimer, float dt) {
    fireDamageTimer += dt; //بيعد الوقت اللي بيعدي عشان playerhealth مينقصش في كل frame
    bool hit = false; //هل النار لمست اللاعب 
    //هنا بيلف علي كل النار اللي احنا حطناهم 
    for (auto& f : fires) {
        f.drop.y += f.fallSpeed * dt; //بنحرك النار لتحت علي حسب سرعتها 
        //بنرجعها تاني لما النار تلمس الارض 
        if (f.drop.y > f.start.y + f.fallDistance) {
            f.drop.y = f.start.y + f.startGap;  //بنرجع النار لنقطة البداية
            f.frame = 1;
        }
        //المعادله دي بتحسب النار اللي نزلت كام في الميه من مشورها الكلي بتكون رقم بين ال 0 و 1 
        float prog = std::clamp((f.drop.y - f.start.y - f.startGap) / (f.fallDistance - f.startGap), 0.f, 1.f);

        float frameValue = prog * (FIRE_FRAMES - 2);//بنحسب النتيجة بتكون رقم بال decimal
        f.frame = 1 + (int)frameValue; //بنحوله لرقم صحيح

        //Collision Detection عشان لما يلمس النار مش لما يقرب فا بنعمل frame وهمي حولين النار بحيث النار تكون حولين الframe بالضبط
        if (sf::FloatRect(f.drop.x - 15, f.drop.y - 15, 30, 30).contains(playerPos)) hit = true;
    }
    //لو لمس النار أل health بتاعه يقل 
    if (hit && fireDamageTimer >= 0.5f) {
        playerHealth -= 5;
        fireDamageTimer = 0; //عشان يبدا يعد نص ثانيه من الاول و جديد
    }
}

void drawEnemies(sf::RenderWindow& window, std::vector<Enemy>& enemies, EneTextures& tex, sf::Vector2f playerPos) {
    for (auto& e : enemies) {
        if (!e.alive) continue;

        sf::Sprite s;
        // رسم الأعداء حسب النوع (1 أو 2 أو 3)
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

            // رسم الطلقات الصفراء
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
//بنرسم النار 
void drawFires(sf::RenderWindow& window, std::vector<FireTrap>& fires, sf::Texture& tex) {
    for (auto& f : fires) {
        sf::Sprite s(tex);
        s.setOrigin(FIRE_W / 2.f, FIRE_H / 2.f);
        s.setScale(f.scale, f.scale); //حجمها
        s.setTextureRect({ 0,0,FIRE_W,FIRE_H }); //اول frame في الصورة الثابت
        s.setPosition(f.start);
        window.draw(s);
        s.setTextureRect({ 0, f.frame * FIRE_H, FIRE_W, FIRE_H });
        s.setPosition(f.drop);
        window.draw(s);
    }
}