#pragma once
#include <raylib.h>
#include "entity.hpp"

enum Actions {

    None = -1,
    Digging,
    Harvasting = 4,
};

enum Direction {

    Down = 0,
    Up,
    Left,
    Right,
};

class Player : public Entity {

    public:

        Texture2D actionImage = LoadTexture("Assets/Player/PlayerActions.png");

        Player(Rectangle destRect, int speed, int frameX, int frameY);
        ~Player();

        Actions getActionState() { return actions; };
        Direction getDirectionState() { return direction; };
        Rectangle getHitBox() { return hitBox; };

        void update();


    private:

        void drawWalking();
        void drawActions();
        void manageHitBox();

        bool idle = true;

        Rectangle hitBox;
        Actions actions = None;
        Direction direction = Down;

        void animationLogic();
};