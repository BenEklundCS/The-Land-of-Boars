//
// Created by ben on 5/20/24.
//

#include "../../../include/Game/Level/LevelOne.h"
#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Entities/Objects/MovingPlatform.h"
#include "../../../include/Game/Level/LevelLoader.h"
#include "../../../include/Game/Entities/Objects/Tree.h"
#include "../../../include/Game/Entities/Monsters/Bee.h"
#include "../../../include/Game/Entities/Monsters/Snail.h"

GameStateManager* LevelOne::GetGameState() {

    Vector2 origin {0, 0};

#pragma region main game objects
    auto player = std::make_unique<Player>();
    // Register observers
    auto gameState = GameStateManager::GetInstance();

    gameState->AddObject(std::move(player));
#pragma endregion

#pragma region platforms
    // Spawn platforms into the gameState with absolute positions
    auto platform3 = std::make_unique<Platform>(3200 - origin.x, 700 - origin.y, 500, 25, BLACK);
    auto moving_platform = std::make_unique<MovingPlatform>(std::move(platform3), Vector2{0, 0}, Vector2{-700, 700}, 500.0f, false, true);
    auto platform4 = std::make_unique<Platform>(550 - origin.x, 400 - origin.y, 500, 50, BLACK);
    auto moving_platform2 = std::make_unique<MovingPlatform>(std::move(platform4), Vector2{-200, 200}, Vector2{0, 0}, 200.0f, true, false);

    // Adding additional platforms with consistent spacing
    for (int i = 0; i < 4; i++) {
        auto p = std::make_unique<Platform>(550 + i * 1000 - origin.x, 600 - i * 300 - origin.y, 500, 50, BLACK);
        gameState->AddObject(std::move(p));
    }

    gameState->AddObject(std::move(moving_platform));
    gameState->AddObject(std::move(moving_platform2));

#pragma endregion

#pragma region game tiles
    // Get the TileManager
    auto tileManager = std::make_unique<TileManager>(Vector2{-2000 - origin.x, 250 - origin.y});
    // Get the LevelLoader and use it to make a tileMap to load
    auto levelLoader = std::make_unique<LevelLoader>();
    auto tileMap = levelLoader->LoadLevel("../Levels/map_level_one.txt");
    tileManager->CreateTiles(tileMap);
    gameState->SetTileManager(std::move(tileManager));
#pragma endregion

#pragma region monsters
    // Spawn in and add monsters to the game
    auto monster1 = std::make_unique<Boar>(1000 - origin.x, 200 - origin.y, 300, 300, MonsterState::DEFAULT);
    auto monster2 = std::make_unique<Boar>(2000 - origin.x, 500 - origin.y, 100, 100, MonsterState::DEFAULT);

    gameState->AddObject(std::move(monster1));
    gameState->AddObject(std::move(monster2));

    // Add additional boars in a line
    for (int i = 0; i < 10; i++) {
        auto monster3 = std::make_unique<Boar>(2000 + i * 50 - origin.x, 500 - origin.y, 100, 100, MonsterState::DEFAULT);
        gameState->AddObject(std::move(monster3));
    }

    // Bee experiment
    auto bee = std::make_unique<Bee>(100, 100, 300, 300, MonsterState::DEFAULT);
    gameState->AddObject(std::move(bee));

    // Snail
    auto snail = std::make_unique<Snail>(1500 - origin.x, 300 - origin.y, 100, 100, MonsterState::DEFAULT);
    gameState->AddObject(std::move(snail));

#pragma endregion

#pragma region trees
    auto tree = std::make_unique<Tree>(2500 - origin.x, 375 - origin.y, GREEN_TREE_TEXTURE);
    gameState->AddObject(std::move(tree));
#pragma endregion

    return gameState;
}
