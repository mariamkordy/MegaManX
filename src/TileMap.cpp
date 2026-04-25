#include "TileMap.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>

using namespace std;
using namespace tmx;

bool loadTileMap(TileMap& map, const string& tmxFilePath,
    const string& tilesetImagePath)
{
    Map tmxMap;

    if (!tmxMap.load(tmxFilePath))
        return false;

    // texture
    if (!map.tileset.loadFromFile(tilesetImagePath))
        return false;

    // A vector of tilesets. MUST BE A VECTOR (Documentation says so)
    const auto& tileSets = tmxMap.getTilesets();
    if (tileSets.empty()) {
        cout << "Tile sets not found\n";
        return false;
    }
    //Gets the tile size of the first tile set
    map.tileSize = tileSets[0].getTileSize();
    map.width = tmxMap.getTileCount().x;
    map.height = tmxMap.getTileCount().y;

    //forms the vertices into squares (quads)
    map.vertices.setPrimitiveType(Quads);
    map.vertices.resize(map.width * map.height * 4);

    const auto& layers = tmxMap.getLayers();

    for (const auto& layer : layers)
    {
        if (layer->getType() != Layer::Type::Tile)
            continue;

        const auto* tileLayer = layer->getLayerAs<TileLayer>();
        const auto& tiles = tileLayer->getTiles();

        for (size_t i = 0; i < tiles.size(); ++i)
        {
            const auto& tile = tiles[i];

            if (tile.ID == 0)
                continue; // empty tile

            unsigned x = i % map.width;
            unsigned y = i / map.width;

            sf::Vertex* quad = &map.vertices[i * 4];

            // position on screen
            float px = x * map.tileSize.x;
            float py = y * map.tileSize.y;

            quad[0].position = { px, py };
            quad[1].position = { px + map.tileSize.x, py };
            quad[2].position = { px + map.tileSize.x, py + map.tileSize.y };
            quad[3].position = { px, py + map.tileSize.y };

            // texture coords
            unsigned tu = (tile.ID - 1) % (map.tileset.getSize().x / map.tileSize.x);
            unsigned tv = (tile.ID - 1) / (map.tileset.getSize().x / map.tileSize.x);

            quad[0].texCoords = { tu * map.tileSize.x, tv * map.tileSize.y };
            quad[1].texCoords = { (tu + 1) * map.tileSize.x, tv * map.tileSize.y };
            quad[2].texCoords = { (tu + 1) * map.tileSize.x, (tv + 1) * map.tileSize.y };
            quad[3].texCoords = { tu * map.tileSize.x, (tv + 1) * map.tileSize.y };
        }
    }

    return true;
}

void drawTileMap(const TileMap& map, RenderWindow& window)
{
    RenderStates states;
    states.texture = &map.tileset;

    window.draw(map.vertices, states);
}