#include "gui.hpp"
#include <iostream>

// Expericence with GUI: PAIN

GUI::GUI() {

    images[0] = LoadTexture("Assets/Objects/Plants.png");
    images[1] = LoadTexture("Assets/Objects/Coin.png");
    images[2] = LoadTexture("Assets/Objects/SpeechBox.png");

    otherImages[0] = LoadTexture("Assets/Objects/DailogBox.png");
    otherImages[1] = LoadTexture("Assets/Objects/Emoji.png");
}

void GUI::update() {

    if(IsKeyPressed(KEY_E)) {

        randWheat1 = GetRandomValue(1, 10);
        randWheat2 = GetRandomValue(7, 20);
        randWheat3 = GetRandomValue(18, 28);

        randTomato1 = GetRandomValue(1, 5);
        randTomato2 = GetRandomValue(8, 11);
        randTomato3 = GetRandomValue(13, 21);

        money1 = GetRandomValue(0, 202);
        money2 = GetRandomValue(94, 251);
        money3 = GetRandomValue(120, 372);

        percentScam1 = GetRandomValue(3, 31);
        percentScam2 = GetRandomValue(34, 54);
        percentScam3 = GetRandomValue(40, 80);

        dealerNameIndex = GetRandomValue(0, 6);

        toggleDealerScreen = !toggleDealerScreen;
    }

    if(toggleDealerScreen) {

        drawSellings();

    } else draw();

    if(mouseClicked(destRect[0])) 
        selectedPlant = Wheat;
    else if(mouseClicked(destRect[1]))
        selectedPlant = Tomato;

    if(mouseHover(destRect[0]))
        WheatColor = {255, 255, 255, 150};
    else WheatColor = WHITE;

    if(mouseHover(destRect[1])) 
        TomatoColor = {255, 255, 255, 150};
    else TomatoColor = WHITE;

    srcRect[0] = {
        0, 0,
        (float) images[0].width / 6,
        (float) images[0].height / 2
    };
    destRect[0] = {
        120, 8,
        40, 40
    };

    srcRect[1] = srcRect[0];
    srcRect[1].y = srcRect[1].height;
    destRect[1] = {
        200, 8,
        40 ,40
    };


    srcRect[2] = {
        0, 0,
        (float) images[1].width / 12,
        (float) images[1].height
    };
    destRect[2] = {
        10, 10,
        40, 40
    };

    srcRect[3] = {
        0, 0,
        (float) images[2].width,
        (float) images[2].height
    };
    destRect[3] = {
        0, -10,
        300, 80
    };

    otherSrcRect[2] = otherSrcRect[1];
    otherSrcRect[2].x = otherSrcRect[2].width * 2;
    
    otherSrcRect[3] = otherSrcRect[2];
    otherSrcRect[3].x *= 2;

    otherSrcRect[1] = {

        otherSrcRect[1].width, 
        otherSrcRect[1].height * 2, 
        (float) otherImages[1].width / 5,
        (float) otherImages[1].height / 19
    };

    otherSrcRect[0] = {

        0, 0,
        (float) otherImages[0].width,
        (float) otherImages[0].height
    };
}

bool GUI::mouseClicked(Rectangle rect) {

    if(
        CheckCollisionPointRec(GetMousePosition(), rect) 
        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    ) return true;
    

    return false;
}

bool GUI::mouseHover(Rectangle rect) {

    if(CheckCollisionPointRec(GetMousePosition(), rect)) 
        return true;

    return false;
}

std::string GUI::formatZeros(int num, int width) {

    std::string numText = std::to_string(num);

    int leadingZero = width - numText.length();
    
    numText = 'x' + std::string(leadingZero, '0') + numText;

    return numText;

}

void GUI::draw() {

    DrawTexturePro(
        images[2],
        srcRect[3], destRect[3],
        {0, 0}, 0, WHITE
    );

    DrawTexturePro(
        images[1],
        srcRect[2], destRect[2],
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(coins, 4).c_str(), 50, 20, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[0], destRect[0],
        {0, 0}, 0, WheatColor
    );

    DrawText(formatZeros(wheatSeeds, 2).c_str(), 160, 20, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[1], destRect[1],
        {0, 0}, 0, TomatoColor
    );

    DrawText(formatZeros(tomatoSeeds, 2).c_str(), 240, 20, 20, BLACK);

}

void GUI::drawSellings() {

    std::string dealers[] = {
        "Harry", "Joe", "Aaron", 
        "Jack", "Charlie", "Anne", 
        "Freya", "Isla", "Molly"
    };

    DrawTexturePro(
        images[2],
        srcRect[3], {100, -35, 780, 700},
        {0, 0}, 0, WHITE
    );

    DrawText("Dealers:", 170, 90, 40, BLACK);


        DrawTexturePro(
            otherImages[0],
            otherSrcRect[0], {150, 125, 700, 150},
            {0, 0}, 0, DealerBackground1
        );

        if(mouseHover({150, 125, 700, 150})) DealerBackground1.a = 200;
        else DealerBackground1 = WHITE;

        if(mouseClicked({150, 125, 700, 150})) {

            getResourcesForPlayer(
                money1, randWheat1, 
                randTomato1, percentScam1
            );
        }

        DrawTexturePro(
            otherImages[0],
            otherSrcRect[0], {150, 125 * 2, 700, 150},
            {0, 0}, 0, DealerBackground2
        );

        if(mouseHover({150, 125 * 2, 700, 150})) DealerBackground2.a = 200;
        else DealerBackground2 = WHITE;

        if(mouseClicked({150, 125 * 2, 700, 150})) {

            getResourcesForPlayer(
                money2, randWheat2, 
                randTomato2, percentScam2
            );
        }

        DrawTexturePro(
            otherImages[0],
            otherSrcRect[0], {150, 125 * 3, 700, 150},
            {0, 0}, 0, DealerBackground3
        );

        if(mouseHover({150, 125 * 3, 700, 150})) DealerBackground3.a = 200;
        else DealerBackground3 = WHITE;

        if(mouseClicked({150, 125 * 3, 700, 150})) {

            getResourcesForPlayer(
                money3, randWheat3, 
                randTomato3, percentScam3
            );
        }

        DrawText(
            dealers[dealerNameIndex].c_str(),
            300, 143, 20, BLACK
        );

        DrawText(
            dealers[dealerNameIndex + 1].c_str(),
            300, 133 * 2, 20, BLACK
        );

        DrawText(
            dealers[dealerNameIndex + 2].c_str(),
            300, 133 * 3 - 5, 20, BLACK
        );

    // 1 part------------------------------------------------

    DrawText(
        (std::to_string(percentScam1) + "% Scam").c_str(), 
        620, 200, 30, BLACK
    );

    DrawTexturePro(
        images[1],
        srcRect[2], {320, 190, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(money1, 4).c_str(), 358, 200, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[0], {500, 205, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randWheat1, 2).c_str(), 540, 220, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[1], {500, 170, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randTomato1, 2).c_str(), 540, 190, 20, BLACK);

    // 2 part------------------------------------------------

    DrawText(
        (std::to_string(percentScam2) + "% Scam").c_str(), 
        620, 325, 30, BLACK
    );

    DrawTexturePro(
        images[1],
        srcRect[2], {320, 315, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(money2, 4).c_str(), 358, 325, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[0], {500, 330, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randWheat2, 2).c_str(), 540, 310, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[1], {500, 295, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randTomato2, 2).c_str(), 540, 345, 20, BLACK);

    // 3 part-------------------------------------------------

    DrawText(
        (std::to_string(percentScam3) + "% Scam").c_str(), 
        620, 445, 30, BLACK
    );

    DrawTexturePro(
        images[1],
        srcRect[2], {320, 440, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(money3, 4).c_str(), 358, 450, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[0], {500, 455, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randWheat3, 2).c_str(), 540, 470, 20, BLACK);

    DrawTexturePro(
        images[0],
        srcRect[1], {500, 420, 40, 40},
        {0, 0}, 0, WHITE
    );

    DrawText(formatZeros(randTomato3, 2).c_str(), 540, 435, 20, BLACK);

    // other---------------------------------------------------

    DrawTexturePro(
        otherImages[1],
        otherSrcRect[1], {183, 160, 80, 80},
        {0, 0}, 0, WHITE
    );

    DrawTexturePro(
        otherImages[1],
        otherSrcRect[2], {183, 160 + 125, 80, 80},
        {0, 0}, 0, WHITE
    );

    DrawTexturePro(
        otherImages[1],
        otherSrcRect[3], {183, 160 + 125 * 2, 80, 80},
        {0, 0}, 0, WHITE
    );

}

void GUI::getResourcesForPlayer(
    int moneyToTake, int wheatToGive, 
    int tomatoToGive, int percentScam
) 
{

    if(coins >= moneyToTake) {

        if(GetRandomValue(0, 100) > percentScam) {

            coins -= moneyToTake;
            tomatoSeeds += tomatoToGive;
            wheatSeeds += wheatToGive;
        } else {

            DrawText("SCAMMED!", (GetScreenWidth() / 2) - 100, 0, 100, RED);

            coins -= moneyToTake + percentScam;
            tomatoSeeds += 1;
            wheatSeeds += 2;
        }
    } else {

        std::cout << "NO\n";
    }

    toggleDealerScreen = false;

}