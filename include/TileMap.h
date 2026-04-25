#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct TileMap
{
    sf::VertexArray vertices;   // geometry (what gets drawn)
    sf::Texture tileset;        // tileset image
    sf::Vector2u tileSize;      // size of one tile
    unsigned width = 0;
    unsigned height = 0;
};

// Loads a .tmx file and builds vertex data
bool loadTileMap(TileMap& map, const std::string& tmxFilePath, const std::string& tilesetImagePath);

// Draws the map
void drawTileMap(const TileMap& map, sf::RenderWindow& window);