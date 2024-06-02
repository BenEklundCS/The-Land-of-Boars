//
// Created by ben on 5/20/24.
//

#include "../../../include/Game/Level/LevelOne.h"
#include "../../../include/Game/Management/TileManager.h"

std::unique_ptr<GameStateManager> LevelOne::GetGameState() {
#pragma region main game objects
    auto player = std::make_unique<Player>();
    auto gameState = std::make_unique<GameStateManager>();

    gameState->AddObject(std::move(player));
#pragma endregion


#pragma region platforms
    auto platform3 = std::make_unique<Platform>(1300, (float) GetScreenHeight() - 700, 500, 50, BLACK);
    auto platform4 = std::make_unique<Platform>(550, 300, 500, 50, BLACK);

    gameState->AddObject(std::move(platform3));
    gameState->AddObject(std::move(platform4));
#pragma endregion


#pragma region game tiles
    // Get the TileManager
    auto tileManager = std::make_unique<TileManager>(Vector2{-2000, 0});
    // Define the main game map
    const int mapWidth = 500;
    const int mapHeight = 50;
    const int tilesStartAtX = 20;
    const int tilesStartAtY = 15;
    std::vector<std::vector<int>> tileMap(mapHeight, std::vector<int>(mapWidth));
    for (int i = 0; i < mapWidth; i++)
        tileMap[tilesStartAtY-1][i] = 2;
    for (int i = 0; i < mapWidth; i++)
        for (int j = tilesStartAtY; j < mapHeight; j++)
            tileMap[j][i] = 1;


    tileManager->CreateTiles(tileMap);
    std::vector<std::unique_ptr<Tile>> tiles = tileManager->GetTiles();

    for (auto& tile : tiles) {

        gameState->AddObject(std::move(tile));

    }
#pragma endregion


#pragma region monsters
    auto monster1 = std::make_unique<Boar>(1000, 200, 100, 100, MonsterState::PACING);
    auto monster2 = std::make_unique<Boar>(2000, GetScreenHeight() - 200, 100, 100, MonsterState::DEFAULT);

    gameState->AddObject(std::move(monster1));
    gameState->AddObject(std::move(monster2));
#pragma endregion
    return gameState;
}
