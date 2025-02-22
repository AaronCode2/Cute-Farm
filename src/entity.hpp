#pragma once
#include <raylib.h>
#include <iostream>

class Entity {

    public:

    Entity(Rectangle destRect, int frameX, int frameY, std::string imageSrc);
    ~Entity();

    void update() { draw(); };

    protected:

    Rectangle destRect;
    int frameX;
    int frameY;

    int currentFrame = 0;
    int elapsedFrame = 0;

    Texture2D image;
    std::string imageSrc;
    Rectangle srcRect;

    void draw();
    int animate(int frameMax, int frameBuffer);
};