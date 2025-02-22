#pragma once
#include <raylib.h>
#include <iostream>
#include "TileManger.hpp"
#include "tile.hpp"
#include "player.hpp"


namespace utils {
    
    void processCollision(
        Rectangle &othertile, 
        Rectangle prevRect, 
        Rectangle player, int speed
    );

    bool harvastingStatus(Player &player, Tile &tile, Rectangle tileSelRect);
    bool plantDirtStatus(Player &player, Tile &tile, Rectangle tileSelRect);
    bool checkCollision(Player &player, Tile &tile);

    bool plantableStatus(
        Player &player, Tile &tile, 
        Rectangle tileSelRect, TileManger &tileManger
    );
}