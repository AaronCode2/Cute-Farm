#include "plants.hpp"

Texture2D Plant::image;

Plant::Plant(Rectangle destRect, PlantType plantType) {

    this->destRect = destRect;
    this->plantType = plantType;
}

void Plant::update() {
    
    draw();

    grow(
        GetRandomValue(
            GetRandomValue(30, 40),
            GetRandomValue(60, 120)
        )
    );
}

void Plant::grow(int random) {

    bool alreadyIncremented = false;

    if(GetTime() - time >= random) {

        if(growthStage == Baby && !alreadyIncremented) {

            growthStage = GrowingBaby;
            alreadyIncremented = true;
        } else if(growthStage == GrowingBaby && !alreadyIncremented) {

            growthStage = Unharvastable;
            alreadyIncremented = true;
        } else growthStage = harvastable;
        
        time = GetTime();
    }
}

bool Plant::isHarvastable() {

    return (growthStage == harvastable) ? true : false;
}

void Plant::draw() {

    srcRect.y = (plantType == Tomato) ? srcRect.height * 1 : 0;
    srcRect.x = srcRect.width * growthStage;
    srcRect.width = image.width / 6;
    srcRect.height = image.height / 2;

    DrawTexturePro(
        image,
        srcRect, destRect,
        {0, 0}, 0, WHITE
    );
}
