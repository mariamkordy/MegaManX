#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
using namespace sf;
using namespace std;

struct Ground{
	RectangleShape rectangle;
};


void collision(Player& player, const std::vector<Ground>& grounds);