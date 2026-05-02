#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.h"

using namespace sf;
using namespace std;

// CHECKPOINT
struct Checkpoint
{
    RectangleShape shape;
    bool activated;
};

void setupPlayer(Player& player);
Checkpoint createCheckpoint(float x, float y);
void movePlayer(Player& player, float deltaTime);
void applyDamage(Player& player, int damage);
void handleCheckpoints(Player& player, vector<Checkpoint>& checkpoints,
    Vector2f& lastCheckpointPos, int healthAmount, int maxHealth);
void respawn(Player& player, Vector2f lastCheckpointPos);
void drawAll(RenderWindow& window, Player& player,
    vector<Checkpoint>& checkpoints, Text& healthText,Text& statusText);

