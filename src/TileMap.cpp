#include "TileMap.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <iostream>

using namespace tmx;
using namespace std;
using namespace sf;



bool loadTileMap(TileMap& map, const string& tmxFilePath, const string& tilesetImagePath)
{
    Map tmxMap;

    if (!tmxMap.load(tmxFilePath))
    {
        cout << "Failed to load TMX\n";
        return false;
    }

    if (!map.tileset.loadFromFile(tilesetImagePath))
    {
        cout << "Failed to load tileset texture\n";
        return false;
    }
    //Retrieves all tilesets. If not found, returns false.
    const auto& tileSets = tmxMap.getTilesets(); 
    if (tileSets.empty())
        return false;
    //LEAVE THIS PART ALONE
    auto tmxTileSize = tileSets[0].getTileSize();

    map.tileSize = sf::Vector2f(tmxTileSize.x, tmxTileSize.y);
    //Calculates the size of the map (measured in tiles).
    map.width = tmxMap.getTileCount().x;
    map.height = tmxMap.getTileCount().y;
    
    //Ensures the vertex array is understood as an array that stores vertices of a quad
    map.vertices.setPrimitiveType(sf::Quads);
    map.vertices.resize(map.width * map.height * 4);

    //Sets the size of the map in tiles, and sets the property "isGround" to false (initially).
    map.isGround.resize(map.width * map.height, false);

    const auto& layers = tmxMap.getLayers();

    //Iterates through layers; Ignores anything(like photo layers) that's not a tile layer
    for (const auto& layer : layers)
    {
        if (layer->getType() != Layer::Type::Tile)
            continue;
        //getLayerAs returns a (smart) pointer to the layer, and takes a template argument that tells it which type to interpret it as (tile, image, etc) PER DOCUMENTATION
        //A smart pointer is just like a regular/raw pointer, but it handles memory by itself so you don't have to woory about memory leaks
        //USING REFERENCES INSTEAD OF POINTERS
        //reference (from a smart pointer) to the tile layer => tile layer => tiles (a vector of tile structs). The tile struct is defined by tmx. It contains the ID of each tile (empty, ground, wall, etc all referred to by numbers)
        const TileLayer& tileLayer = layer->getLayerAs<TileLayer>();
        const auto& tiles = tileLayer.getTiles();

        int numberOfTiles = tiles.size();
        for (int i = 0; i < numberOfTiles; ++i)
        {
            const auto& tile = tiles[i]; //ref to each tile inside the tiles vector
            //empty tile
            if (tile.ID == 0)
                continue;

            //The following lines turn the index of a tile inside the vector into its position in the grid
            //COLUMN
            int x = i % map.width;

            //ROW
            int y = i / map.width;


            //Vertex in this context is a struct that stores the coordinates of the "physical" vertex 
            // of a tile, and the coordinate of the tile image that should be used.
            //Quad is like a small array of 4 elements, that stores 4 vertices. It is a pointer to a vertex struct
            sf::Vertex* quad = &map.vertices[i * 4];


            //CONVERT FROM GRID POSITION (IN Tiled) INTO PIXEL POSITION
            float px = x * map.tileSize.x;
            float py = y * map.tileSize.y;

            // positions. REMEMBER: the default position is the top left corner, hence the equations below
            //top left, top right, bottom right, bottom left
            quad[0].position = { px, py };
            quad[1].position = { px + map.tileSize.x, py };
            quad[2].position = { px + map.tileSize.x, py + map.tileSize.y };
            quad[3].position = { px, py + map.tileSize.y };

            // texture coords
            //same logic as x and y in the grid position.

            int tilesPerRow = map.tileset.getSize().x / map.tileSize.x;
            int tu = (tile.ID - 1) % (tilesPerRow);
            int tv = (tile.ID - 1) / (tilesPerRow);

            quad[0].texCoords = { tu * map.tileSize.x, tv * map.tileSize.y };
            quad[1].texCoords = { (tu + 1) * map.tileSize.x, tv * map.tileSize.y };
            quad[2].texCoords = { (tu + 1) * map.tileSize.x, (tv + 1) * map.tileSize.y };
            quad[3].texCoords = { tu * map.tileSize.x, (tv + 1) * map.tileSize.y };

            // OPTIONAL: mark all tiles as ground for now
            // (you can replace this later with Tiled properties)
            map.isGround[i] = true;
        }
    }

    return true;
}

// ----------------------------------------------------
// DRAW MAP
// ----------------------------------------------------
void drawTileMap(const TileMap& map, sf::RenderWindow& window)
{
    sf::RenderStates states;
    states.texture = &map.tileset;

    window.draw(map.vertices, states);
}

// ----------------------------------------------------
// WORLD → TILE INDEX
// ----------------------------------------------------
int getTileIndex(const TileMap& map, float x, float y)
{
    int tileX = static_cast<int>(x) / map.tileSize.x;
    int tileY = static_cast<int>(y) / map.tileSize.y;

    if (tileX < 0 || tileY < 0 || tileX >= (int)map.width || tileY >= (int)map.height)
        return -1;

    return tileY * map.width + tileX;
}