//
// Created by ben on 5/20/24.
//

#include "../../../include/Game/Level/LevelOne.h"
#include "../../../include/Game/Management/TileManager.h"

std::unique_ptr<GameStateManager> LevelOne::GetGameState() {
    auto player = std::make_unique<Player>();
    auto gameState = std::make_unique<GameStateManager>();

    gameState->AddObject(std::move(player));

    auto platform1 = std::make_unique<Platform>(0, (float) GetScreenHeight() - 100, (float) GetScreenWidth(), 100,
                                                DARKBROWN);
    auto platform2 = std::make_unique<Platform>(550, (float) GetScreenHeight() - 400, 500, 50, BLACK);
    auto platform3 = std::make_unique<Platform>(1300, (float) GetScreenHeight() - 700, 500, 50, BLACK);
    auto platform4 = std::make_unique<Platform>(550, 300, 500, 50, BLACK);

    float floorHeight = (float) GetScreenHeight() - 100;

    /*
    for (int i = 0; i < 4000; i++) {
        auto tile = std::make_unique<Tile>(-1000 + i * 100, floorHeight - 1000, TILE_GRASS_TEXTURE);
        gameState->AddObject(std::move(tile));
    }



    for (int i = 0; i < 100000; i++) {
        auto boar = std::make_unique<Boar>(1000 + i * 10, 200, 100, 100, MonsterState::PACING);;
        gameState->AddObject(std::move(boar));
    }
     */

    auto tileManager = std::make_unique<TileManager>(Vector2{1000, 1000});

    std::vector<std::vector<int>> tileMap = {
            {0, 0, 1, 1, 0, 1, 1},
            {1, 1, 2, 2, 1, 0, 0, 1},
            {1, 1, 0, 0, 1, 0, 0},
            // Add more rows as needed
    };

    tileManager->CreateTiles(tileMap);
    std::vector<std::unique_ptr<Tile>> tiles = tileManager->GetTiles();

    for (auto& tile : tiles) {
        if (tile != nullptr) {
            gameState->AddObject(std::move(tile));
        }
    }

    gameState->AddObject(std::move(platform1));
    gameState->AddObject(std::move(platform2));
    gameState->AddObject(std::move(platform3));
    gameState->AddObject(std::move(platform4));

    auto monster1 = std::make_unique<Boar>(1000, 200, 100, 100, MonsterState::PACING);
    auto monster2 = std::make_unique<Boar>(2000, GetScreenHeight() - 200, 100, 100, MonsterState::DEFAULT);

    gameState->AddObject(std::move(monster1));
    gameState->AddObject(std::move(monster2));

    return gameState;
}
