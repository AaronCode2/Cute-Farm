#include "tile.hpp"
#include <iostream>

Texture2D Tile::image[5];

Tile::Tile(Rectangle destRect, Tiletype tiletype, int frameX, int frameY) {

    this->destRect = destRect;
    this->tiletype = tiletype;
    this->frameX = frameX;
    this->frameY = frameY;

    switch(tiletype) {

        case CollisionBox:
            break;

        case Hills:
        case Grass:
        case Dirt:

            srcRect = {
                (float) (image[getImageID()].width / 11) * frameX, 
                (float) (image[getImageID()].height / 7) * frameY,
                (float) image[getImageID()].width / 11,
                (float) image[getImageID()].height / 7 
            };

            break;

        case Decoration:
        case TreeTop:

            srcRect = {
                (float) (image[getImageID()].width / 9) * frameX, 
                (float) (image[getImageID()].height / 5) * frameY,
                (float) image[getImageID()].width / 9,
                (float) image[getImageID()].height / 5 
            };
            
            break;

        case ColDecoration:

            srcRect = {
                (float) (image[getImageID()].width / 9) * frameX, 
                (float) (image[getImageID()].height / 5) * frameY,
                (float) image[getImageID()].width / 9,
                (float) (image[getImageID()].height / 5) 
            };

            // Don't tell me why this is here as it just works!

            srcRect.height -= 11;

            break;
    }

}

void Tile::update() {

    if(CheckCollisionRecs(destRect, screenRect)) 
        draw();

}

void Tile::drawAdditionals() {

    // To draw the Truck 

    if(tiletype == ColDecoration) {

        Rectangle srcRect2 = {

            srcRect.x,
            srcRect.y + 5,
            srcRect.width,
            srcRect.height + 11
        };

        Rectangle destRect2 = {

            destRect.x,
            destRect.y + destRect.height,
            destRect.width,
            destRect.height + 25
        };

        DrawTexturePro(
            image[getImageID()],
            srcRect2, destRect2,
            {0, 0}, 0,
            WHITE
        );
    }
}

int Tile::getType() {

    return (int) tiletype;
}

Rectangle Tile::getColRect() {

    Rectangle colRect = destRect;

    if(tiletype == Hills && frameY == 2)
        colRect.height -= 30;

    if(tiletype == ColDecoration) {

        colRect = {
            destRect.x + 16,
            destRect.y + 21,
            destRect.width - 33,
            destRect.height - 19
        };
    }

    return colRect;
}

void Tile::draw() {

    if(tiletype != ColDecoration) {

        DrawTexturePro(
            image[getImageID()], 
            srcRect, destRect,
            {0, 0}, 0, WHITE
        );
    } else {

        // To Draw the Bush

        destRect.height = 25;

        DrawTexturePro(
            image[getImageID()], 
            srcRect, destRect,
            {0, 0}, 0, WHITE
        );

    }

}

int Tile::getImageID() {

    switch(tiletype) {

        case Decoration:
        case ColDecoration:
        case TreeTop:

            return 2;
            break;

        case Hills:

            return 1;
            break;

        case Grass:

            return 0;
            break;

        case Dirt:

            return 3;
            break;

        case CollisionBox:
            return -1;
            break;
    }

    return 0;
}
