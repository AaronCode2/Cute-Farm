#include "game.hpp"
#include "utils.hpp"

Game::Game() {

    SetWindowIcon(icon);
    UnloadImage(icon);

    tileManger.createTile();
    runGame();
}

void Game::updateGame() {

    tileManger.drawTilesBeforePlayerDrawn();
    tileManger.drawPlants();
    managePlants();
    manageAddDirtTiles();

    player.update();

    tileManger.drawTilesAfterPlayerDrawn();
    gui.update();

}

bool Game::titleScreen() {

    time += GetFrameTime();
    float yOffset = sin(time * 2.0f) * 20.0f;

    src = {

        0, 
        src.height, 
        (float) playBtn.width / 2,
        (float) playBtn.height / 2
    };

    if(utils::mouseHover(dest)) src.x = src.width;

    if(utils::mouseClicked(dest)) runTitleScreen = true;    
    
    if(!runTitleScreen) {

        DrawText("Cute Farm", 290, 100 + yOffset, 80, PINK);

        DrawTexturePro(
            playBtn,
            src, dest,
            {0, 0}, 0, WHITE
        );
    }

    return runTitleScreen;
}

void Game::checkInput() {

    for(auto &tile : tileManger.tiles) {
        
        prevRect = tile.getColRect();

        tileManger.checkInput(tile.destRect);
        manageCollision(tile);
    }
}

void Game::manageCollision(Tile &tile) {

    if(utils::checkCollision(player, tile)) {

        for(auto &othertile : tileManger.tiles) {

            utils::processCollision(
                othertile.destRect,
                prevRect, player.getHitBox(), 5
            );
        }

        for(auto &plant : tileManger.plants) {

            utils::processCollision(
                plant.destRect,
                prevRect, player.getHitBox(), 5
            );
        } 

    }
}

void Game::manageHarvasting(Tile &tile) {

    if(utils::harvastingStatus(player, tile, tileSelRect)) {

        for(auto it = tileManger.plants.begin(); it < tileManger.plants.end(); it++) {

            if(
                it->isHarvastable() && 
                CheckCollisionRecs(it->destRect, tileSelRect)
            ) 
            {
                if(it->getType() == Wheat) gui.coins += 56;
                else gui.coins += 78;

                it = tileManger.plants.erase(it);
            }
        }
    }
}



void Game::managePlants() {

    // To prevent undefinned Behaviour as it adds and check Plants

    std::vector<Plant> tempPlant;

    for(auto &tile : tileManger.tiles) {

        tileSelRect = {

            tile.getColRect().x + 10,
            tile.getColRect().y + 15,
            tile.getColRect().width - 20,
            tile.getColRect().height - 40
        };

        manageHarvasting(tile);
        
        if(utils::plantableStatus(player, tile, tileSelRect, tileManger)) {

            if(gui.tomatoSeeds > 0 && gui.selectedPlant == Tomato) {

                tempPlant.push_back(Plant(
                    {
                        tile.destRect.x,
                        tile.destRect.y,
                        50, 50
                    },
                    gui.selectedPlant
                ));

                gui.tomatoSeeds--;
                break;
            } else if(gui.wheatSeeds > 0 && gui.selectedPlant == Wheat) {

                tempPlant.push_back(Plant(
                    {
                        tile.destRect.x,
                        tile.destRect.y,
                        50, 50
                    },
                    gui.selectedPlant
                ));

                gui.wheatSeeds--;
                break;
            }
        }
    }

    tileManger.plants.insert(
        tileManger.plants.end(), 
        tempPlant.begin(), 
        tempPlant.end()
    );
}

void Game::manageAddDirtTiles() {

    for(auto &tile : tileManger.tiles) {

        tileSelRect = {

            tile.getColRect().x + 10,
            tile.getColRect().y + 15,
            tile.getColRect().width - 20,
            tile.getColRect().height - 40
        };

        if(utils::plantDirtStatus(player, tile, tileSelRect)) {

            tileManger.tiles.push_back(Tile(
                {
                    tile.destRect.x,
                    tile.destRect.y,
                    50, 50
                },
                Dirt,
                1, 1
            ));
        }
    }
}

void Game::runGame() {

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground({155, 212, 195, 255});

        if(titleScreen()) {
            checkInput();
            updateGame();
        }

        if(IsKeyDown(KEY_Q)) runTitleScreen = false;

        DrawTextureEx(mouse, GetMousePosition(), 0, 2.0f, WHITE);
        HideCursor();

        EndDrawing();
    } CloseWindow();
}

Game::~Game() {

    tileManger.destroyTiles();
}