#include "utils.hpp"

void utils::processCollision(
    Rectangle &othertile, 
    Rectangle prevRect, 
    Rectangle player, int speed
) 
{

    if(
        prevRect.y + prevRect.height <= player.y 
        || prevRect.y >= player.y + player.height
    ) 
    {
        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
            othertile.y -= 5.0f;
            
        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
            othertile.y -= -5.0f;     
    }

    if(
        prevRect.x + prevRect.width <= player.x 
        || prevRect.x >= player.x + player.width
    ) 
    {
        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
            othertile.x -= 5.0f;
            
        if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
            othertile.x -= -5.0f;     
    }
}

bool utils::harvastingStatus(Player &player, Tile &tile, Rectangle tileSelRect) {
    
    if(
        player.getActionState() == Harvasting &&
        tile.getType() == Dirt &&
        CheckCollisionRecs(player.getHitBox(), tileSelRect)
    ) return true;

    return false;
}

bool utils::plantableStatus(
    Player &player, Tile &tile, 
    Rectangle tileSelRect, TileManger &tileManger
) 
{

    bool addPlant = true;

    for(auto &plant : tileManger.plants) { 

        if(CheckCollisionRecs(plant.destRect, tileSelRect)) 
            addPlant = false;
    }

    if( 
        addPlant &&
        player.getActionState() == Digging &&
        tile.getType() == Dirt &&
        CheckCollisionRecs(player.getHitBox(), tileSelRect)
    ) return true;

    return false;
}

bool utils::plantDirtStatus(Player &player, Tile &tile, Rectangle tileSelRect) {

    if(
        player.getActionState() == Digging &&
        tile.getType() != Hills &&
        tile.getType() == Grass &&
        CheckCollisionRecs(player.getHitBox(), tileSelRect)
    ) return true;

    return false;
}

bool utils::checkCollision(Player &player, Tile &tile) {

    if(
        (
            tile.getType() == Hills || 
            tile.getType() == ColDecoration || 
            tile.getType() == CollisionBox
        )
        && CheckCollisionRecs(tile.getColRect(), player.getHitBox())
    ) return true;

    return false;
}
