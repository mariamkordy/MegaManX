#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include "Player.h"
#include<iostream>

using namespace sf;
using namespace std;


enum checkpointstate {
    idle,
    activating,
    used
};

// CHECKPOINT
struct Checkpoint
{
    sf::Sprite sprite;
    sf::Texture idlePosition;
    sf::Texture usedPosition;
    sf::Texture activatingPosition;

    checkpointstate pointstate;
    
    int frame;
    float animationtimer;
    float animationSpeed;
    sf::FloatRect bounds;
    float activationtotaltime;
    //RectangleShape shape;
    //bool activated;
};


void setupPlayer(Player& player);
Checkpoint createCheckpoint(float x, float y);
void movePlayer(Player& player, float deltaTime);
void applyDamage(Player& player, int damage);
void handleCheckpoints(Player& player, vector<Checkpoint>& checkpoints,
    Vector2f& lastCheckpointPos, int healthAmount, int maxHealth,float deltaTime, sf::Sound& cpSound);
void respawn(Player& player, Vector2f lastCheckpointPos);
void drawAll(RenderWindow& window, Player& player,
    vector<Checkpoint>& checkpoints, Text& healthText,Text& statusText);

