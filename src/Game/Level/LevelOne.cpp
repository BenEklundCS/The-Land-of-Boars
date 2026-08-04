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
#include "../../../include/Platform/Globals.h"


/**
 * @brief Initializes the game state for Level One.
 *
 * Creates and adds game objects, tiles, platforms, monsters, and other entities
 * to the game state. Configures their positions, behaviors, and interactions.
 *
 * @return GameStateManager* Pointer to the singleton game state manager with Level One's setup.
 */
GameStateManager* LevelOne::GetGameState() {
    Vector2 origin {0, 0};

#pragma region main game objects
    auto player = std::make_unique<Player>();
    // Tiles are scaled by the window factor (Tile.cpp -> Scale()), so the spawn
    // must be scaled too. SetPosition assigns raw world units and runs *after*
    // the Player ctor's Scale(), so an unscaled literal here desyncs the player
    // from the tile grid at any resolution other than the 2560x1440 base --
    // at 1200x700 it lands in empty space with no floor beneath it.
    constexpr Vector2 spawn{1500, 1500};
    player->SetPosition({spawn.x * WINDOW_SCALE_FACTOR_X, spawn.y * WINDOW_SCALE_FACTOR_Y});
    TraceLog(LOG_INFO, "[LEVEL] player spawn: raw(%.1f, %.1f) -> scaled(%.1f, %.1f)  [scale %.4f, %.4f]",
             spawn.x, spawn.y,
             spawn.x * WINDOW_SCALE_FACTOR_X, spawn.y * WINDOW_SCALE_FACTOR_Y,
             WINDOW_SCALE_FACTOR_X, WINDOW_SCALE_FACTOR_Y);
    // Register observers
    auto gameState = GameStateManager::GetInstance();
    gameState->AddObject(std::move(player));
#pragma endregion

#pragma region platforms
    // Spawn platforms into the gameState with absolute positions
    auto platform3 = std::make_unique<Platform>(5350, 700, 250, 25, BLACK);
    auto moving_platform = std::make_unique<MovingPlatform>(std::move(platform3), Vector2{0, 0}, Vector2{-700, 700}, 250.0f, false, true);
    auto platform4 = std::make_unique<Platform>(2000, 400, 500, 50, BLACK);
    auto moving_platform2 = std::make_unique<MovingPlatform>(std::move(platform4), Vector2{-200, 200}, Vector2{0, 0}, 200.0f, true, false);

    // Adding additional platforms with consistent spacing
    for (int i = 0; i < 4; i++) {
        auto p = std::make_unique<Platform>(550 + i * -19000, 600 - i * 300, 500, 50, BLACK);
        gameState->AddObject(std::move(p));
    }

    gameState->AddObject(std::move(moving_platform));
    gameState->AddObject(std::move(moving_platform2));

#pragma endregion

#pragma region game tiles
    // Get the TileManager
    auto tileManager = std::make_unique<TileManager>(Vector2{-2000, 250});
    // Get the LevelLoader and use it to make a tileMap to load
    auto levelLoader = std::make_unique<LevelLoader>();
    auto tileMap = levelLoader->LoadLevel("../Levels/map_level_one.txt");
    tileManager->CreateTiles(tileMap);
    gameState->SetTileManager(std::move(tileManager));
#pragma endregion

#pragma region monsters
    // Spawn in and add monsters to the game
    auto monster1 = std::make_unique<Boar>(4500, 200, 300, 300, MonsterState::DEFAULT);
    auto monster2 = std::make_unique<Boar>(2000, 500, 100, 100, MonsterState::DEFAULT);

    gameState->AddObject(std::move(monster1));
    gameState->AddObject(std::move(monster2));

    /*
    // Add additional boars in a line
    for (int i = 0; i < 10; i++) {
        auto monster3 = std::make_unique<Boar>(0 + i * 50, 500, 100, 100, MonsterState::DEFAULT);
        gameState->AddObject(std::move(monster3));
    }
    */

    // Bee experiment
    auto bee = std::make_unique<Bee>(5000, 0, 300, 300, MonsterState::DEFAULT);
    gameState->AddObject(std::move(bee));

    // Snail
    auto snail = std::make_unique<Snail>(1500, 300, 100, 100, MonsterState::DEFAULT);
    gameState->AddObject(std::move(snail));

#pragma endregion

#pragma region trees
    auto tree = std::make_unique<Tree>(4500, 120+700, GREEN_TREE_TEXTURE);
    gameState->AddObject(std::move(tree));
#pragma endregion

    return gameState;
}
