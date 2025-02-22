#pragma once
#include <raylib.h>
#include <thread>
#include <chrono>
#include <iostream>

enum PlantType {

    Wheat = 0,
    Tomato
};

enum GrowthStage {

    Seed = 0,
    Baby,
    GrowingBaby,
    Unharvastable,
    harvastable,
    harvasted
};

class Plant {

    public:


        Plant(Rectangle destRect, PlantType plantType);

        void update();
        bool isHarvastable();
        PlantType getType() { return plantType; };

        Rectangle destRect;
        static Texture2D image;

    private:

        void grow(int random);
        void draw();

        double time = GetTime();


        GrowthStage growthStage = Baby;
        Rectangle srcRect;
        PlantType plantType;
};