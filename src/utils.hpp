#pragma once
#include <raylib.h>
#include <iostream>
#include "TileManger.hpp"
#include "tile.hpp"
#include "player.hpp"


namespace utils {
    
    void processCollision(
        Rectangle &othertile, 
        const Rectangle prevRect, 
        const Rectangle player, int speed
    );

    bool mouseHover(Rectangle dest);
    bool mouseClicked(Rectangle dest);

    bool harvastingStatus(Player &player, Tile &tile, const Rectangle tileSelRect);
    bool plantDirtStatus(Player &player, Tile &tile, const Rectangle tileSelRect);
    bool checkCollision(Player &player, Tile &tile);

    bool plantableStatus(Player &player, Tile &tile, const Rectangle tileSelRect, TileManger &tileManger);
}