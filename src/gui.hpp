#pragma once
#include <raylib.h>
#include "plants.hpp"
#include "utils.hpp"

class GUI {

    public:

        GUI();

        void update();

        PlantType selectedPlant = Wheat;

        int coins = 0;
        int wheatSeeds = 5;
        int tomatoSeeds = 3;

    private:

        void draw();
        void drawSellings();

        void getResourcesForPlayer(
            int moneyToTake, int wheatToGive, 
            int tomatoToGive, int percentScam
        );


        bool toggleDealerScreen = false;

        Texture2D images[3];

        Texture2D otherImages[2];

        Color TomatoColor = WHITE;
        Color WheatColor = WHITE;

        Color DealerBackground1 = WHITE;
        Color DealerBackground2 = WHITE;
        Color DealerBackground3 = WHITE;

        int randWheat1 = 0;
        int randWheat2 = 0;
        int randWheat3 = 0;

        int randTomato1 = 0;
        int randTomato2 = 0;
        int randTomato3 = 0;

        int money1 = 0;
        int money2 = 0;
        int money3 = 0;

        int dealerNameIndex = 0;

        int percentScam1 = 0;
        int percentScam2 = 0;
        int percentScam3 = 0;

        Rectangle destRect[4];
        Rectangle srcRect[4];

        Rectangle otherSrcRect[4];

        std::string formatZeros(int num, int width);
};