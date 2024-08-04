//
// Created by ben on 5/20/24.
//

#include "../../../include/Game/Level/LevelOne.h"
#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "../../../include/Game/Management/SoundManager.h"
#include "../../../include/Game/Level/LevelLoader.h"

GameStateManager* LevelOne::GetGameState() {

#pragma region main game objects
    auto player = std::make_unique<Player>();
    // Register observers
    auto gameState = GameStateManager::GetInstance();



    gameState->AddObject(std::move(player));
#pragma endregion


#pragma region platforms
    // Spawn platforms into the gameState
    auto platform3 = std::make_unique<Platform>(1300, 300, 500, 500, BLACK);
    auto moving_platform = std::make_unique<MovingPlatform>(std::move(platform3), Vector2{-200, 200}, Vector2{0, 0}, 100.0f, true, false);
    auto platform4 = std::make_unique<Platform>(550, (float) GetScreenHeight() - 700, 500, 50, BLACK);

    gameState->AddObject(std::move(moving_platform));
    gameState->AddObject(std::move(platform4));

#pragma endregion


#pragma region game tiles
    // Get the TileManager
    auto tileManager = std::make_unique<TileManager>(Vector2{-2000, +250});
    // Get the LevelLoader and use it to make a tileMap to load
    auto levelLoader = std::make_unique<LevelLoader>();
    auto tileMap = levelLoader->LoadLevel("../Levels/map_level_one.txt");
    tileManager->CreateTiles(tileMap);
    std::vector<std::unique_ptr<Tile>> tiles = tileManager->GetTiles();
    // Add those tiles to the game
    for (auto& tile : tiles) {

        gameState->AddObject(std::move(tile));

    }
#pragma endregion


#pragma region monsters
    // Spawn in and add monsters to the game
    auto monster1 = std::make_unique<Boar>(1000, 200, 300, 300, MonsterState::PACING);
    auto monster2 = std::make_unique<Boar>(2000, GetScreenHeight() - 200, 100, 100, MonsterState::DEFAULT);

    gameState->AddObject(std::move(monster1));
    gameState->AddObject(std::move(monster2));

    for (int i = 0; i < 10; i++) {
        auto monster3 = std::make_unique<Boar>(2000 + i*10, GetScreenHeight() - 200, 100, 100, MonsterState::DEFAULT);

        gameState->AddObject(std::move(monster3));
    }
#pragma endregion

    return gameState;
}
