#pragma once
#include "tile.hpp"
#include "player.hpp"
#include "plants.hpp"
#include <fstream>
#include <vector>
#include <thread>
#include <iostream>

struct TileManger {

    public:

        std::vector<Tile> tiles;
        std::vector<Plant> plants;

        void createTile(); 
        void drawTilesBeforePlayerDrawn();
        void drawPlants();
        void drawTilesAfterPlayerDrawn();
        void checkInput(Rectangle &tile);
        void destroyTiles();

    private:

        void loadTexture();
        Tiletype getType(const char letter);
};