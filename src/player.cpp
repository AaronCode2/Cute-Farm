#include "player.hpp"

Player::Player(Rectangle destRect): 
Entity(
    destRect, 4, 4, 
    "../Assets/Player/PlayerWalking.png"
) {}

Player::~Player() {

    UnloadTexture(image);
    UnloadTexture(actionImage);
}

void Player::update() {

    manageHitBox();
    animationLogic();    
}

void Player::drawWalking() {

    if(idle) srcRect.x = 0;  
    else srcRect.x = srcRect.width * animate(frameX, 8);
         
    srcRect.y = srcRect.height * direction;

    DrawTexturePro(
        image,
        srcRect, destRect,
        {0, 0}, 0, WHITE
    );

}

void Player::drawActions() {
 
    srcRect.x = srcRect.width * animate(frameX, 10);
         
    srcRect.y = srcRect.height * (actions + direction);

    DrawTexturePro(
        actionImage,
        srcRect, destRect,
        {0, 0}, 0, WHITE
    );

}

void Player::manageHitBox() {

    hitBox = {

        destRect.x + 40, 
        destRect.y + 31, 
        destRect.width - 80, 
        destRect.height - 64
    }; 
}

void Player::animationLogic() {

    idle = false;

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        direction = Left;
        
    else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        direction = Right;

    else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
        direction = Up;

    else if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
        direction = Down;

    else idle = true;

    if(IsKeyPressed(KEY_ONE))
        actions = Digging;

    else if(IsKeyPressed(KEY_TWO))
        actions = Harvasting;

    else actions = None;

    (actions != None) ? drawActions() : drawWalking(); 
}
