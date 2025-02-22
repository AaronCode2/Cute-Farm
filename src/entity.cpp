#include "entity.hpp"

Entity::Entity(Rectangle destRect, int frameX, int frameY, std::string imageSrc) {

    this->destRect = destRect;
    this->frameX = frameX;
    this->frameY = frameY;
    this->imageSrc = imageSrc;

    image = LoadTexture(imageSrc.c_str());

    srcRect = {0, 0, (float) image.width / frameX, (float) image.height / frameY};

}

void Entity::draw() {

    srcRect.x = srcRect.width * animate(frameX, 8);

    DrawTexturePro(
        image,
        srcRect, destRect,
        {0, 0}, 0, WHITE
    );
}

int Entity::animate(int frameMax, int bufferFrame) {

    elapsedFrame++;

    if(elapsedFrame % bufferFrame == 0) {

        if(currentFrame < frameMax - 1) currentFrame++;
        else currentFrame = 0;
    } 

    return currentFrame;
}

Entity::~Entity() {

    UnloadTexture(image);
}