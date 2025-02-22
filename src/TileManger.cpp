#include "TileManger.hpp"



void TileManger::loadTexture() {


    Plant::image = LoadTexture("Assets/Objects/Plants.png");

    Tile::image[0] = LoadTexture("Assets/Tilesets/Grass.png");
    Tile::image[1] = LoadTexture("Assets/Tilesets/Hills.png");
    Tile::image[2] = LoadTexture("Assets/Objects/Decoration.png");
    Tile::image[3] = LoadTexture("Assets/Tilesets/Dirt.png");
    
}

Tiletype TileManger::getType(const char letter) {

    switch(letter) {

        case 'G': return Grass;
            break;

        case 'D': return Decoration;
            break;

        case 'T': return TreeTop;
            break;

        case 'C': return ColDecoration;
            break;

        case 'X': return CollisionBox;
            break;
    }

    return Grass;
}

void TileManger::createTile() {
        
    loadTexture();

    std::ifstream file("TileMap.txt");

    if(!file.is_open()) std::cerr << "Failed To Open File\n";

        std::string line;

        float y = 0.0f;
        float tileCounterX = 0.0f;
        const int adjust = 48;

        while(std::getline(file, line)) {
            
            tileCounterX = 0.0f;

            if(line.find("#decorations") != std::string::npos) y = 0.0f;

            for(size_t x = 0; x < line.length(); x++) {
                
                switch(line[x]) {
                    
                    case '?': tileCounterX++;
                        break;

                    case 'G':
                    case 'D':
                    case 'T':
                    case 'C':
                    case 'X':

                        tiles.push_back(Tile(
                            {
                                tileCounterX++ * 50,
                                y * 50,
                                50, 50
                            },
                            getType(line[x]),
                            line[x + 1] - adjust, 
                            line[x + 2] - adjust 
                        ));
                        break;

                    case 'H':

                        tiles.push_back(Tile(
                            {
                                tileCounterX * 50,
                                y * 50,
                                50, 50
                            },
                            Grass, 1, 1 
                        ));

                        tiles.push_back(Tile(
                            {
                                tileCounterX++ * 50,
                                y * 50,
                                50, 50
                            },
                            Hills,
                            line[x + 1] - adjust,
                            line[x + 2] - adjust
                        ));
                        break;
                }

            } y++;
        }

    file.close();
}

void TileManger::drawTilesBeforePlayerDrawn() {

    for(auto &tile : tiles) {

        if(tile.getType() != TreeTop && tile.getType() != ColDecoration)
            tile.update();
            
        tile.drawAdditionals();
    }
}

void TileManger::drawPlants() {
    
    for(auto &plant : plants) {

        checkInput(plant.destRect);
        plant.update();
    }
}

void TileManger::drawTilesAfterPlayerDrawn() {
    
    for(auto &tile : tiles) {

        if(tile.getType() == TreeTop || tile.getType() == ColDecoration)
            tile.update(); 
    }
}

void TileManger::checkInput(Rectangle & tile) {
    
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) 
        tile.y -= -5;

    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) 
        tile.y -= 5;

    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) 
        tile.x -= -5;

    if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) 
        tile.x -= 5;
}

void TileManger::destroyTiles() {

    UnloadTexture(Plant::image);

    for(int i = 0; i < 3; i++) {

        UnloadTexture(Tile::image[i]);
    }   
}
