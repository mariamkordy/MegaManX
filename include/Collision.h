#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
using namespace sf;
using namespace std;

struct Ground{
	RectangleShape rectangle;
};

struct Wall {
	RectangleShape rectangle;
};


void collision(Player& player, const std::vector<Ground>& grounds, const std::vector<Wall>& walls);