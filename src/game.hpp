#pragma once
#include <raylib.h>
#include <vector>
#include <cmath>
#include "tile.hpp"
#include "plants.hpp"
#include "TileManger.hpp"
#include "utils.hpp"
#include "gui.hpp"
#include "entity.hpp"
#include "player.hpp"

class Game {

    public:

        Game();
        ~Game(); 

    private:

        Rectangle prevRect = {0, 0, 0, 0};

        Rectangle src;

        bool run = false;
        float time = 0.0f;

        Texture2D playBtn = LoadTexture("../Assets/Objects/Play.png");
        Texture mouse = LoadTexture("Assets/Player/Mouse.png");
        Image icon = LoadImage("Assets/Objects/Egg.png");

        Player player = Player(
            {
                (float) (GetScreenWidth() / 2) - 50, 
                (float) (GetScreenHeight() / 2) - 50, 
                100, 100
            }, 
            6, 4, 4
        );

        void runGame();
        void updateGame();
        bool titleScreen();

        void checkInput();
        void manageCollision(Tile &tile);
        void manageHarvasting(Tile &tile);
        void managePlants();
        void manageAddDirtTiles();

        Rectangle tileSelRect;
        TileManger tileManger;
        GUI gui;
};