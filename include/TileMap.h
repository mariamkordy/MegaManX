#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace sf;
struct TileMap
{
    // Rendering
    sf:: VertexArray vertices; //A vertex array has all coordinates of vertices of tiles, listed after one another
    sf::Texture tileset;

    // Map info
    sf::Vector2f tileSize; 
    int width = 0;
    int height = 0;

    // Collision data
    vector<bool> isGround; //Some tiles return this boolean. These tiles are the ground.
};

// Load map from Tiled (.tmx)
bool loadTileMap(TileMap& map, const string& tmxFilePath, const string& tilesetImagePath);

// Draw map
void drawTileMap(const TileMap& map, RenderWindow& window);

// Helper: convert world position → tile index
int getTileIndex(const TileMap& map, float x, float y);