#pragma once
#include <raylib.h>

enum Tiletype {

    Grass = 0,
    Hills,
    TreeTop,
    ColDecoration,
    Decoration,
    Dirt,
    CollisionBox
};

class Tile {

    public:

        static Texture2D image[5];
        
        Tile(Rectangle destRect, Tiletype tiletype, int frameX, int frameY);

        void update();
        void drawAdditionals();
        int getType();

        Rectangle getColRect();

        Rectangle destRect;

    private:

        int frameX;
        int frameY;
        

        Rectangle screenRect = {
            0, 0, 
            (float) GetScreenWidth(), 
            (float) GetScreenHeight()
        };


        Tiletype tiletype;
        Rectangle srcRect;

        const float size = 0; 

        void draw();
        int getTileID();
};