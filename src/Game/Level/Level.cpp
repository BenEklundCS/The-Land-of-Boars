//
// Created by ben on 5/20/24.
//

#include "../../../include/Game/Level/Level.h"
#include "../../../include/Game/Level/LevelLoader.h"
#include "../../../include/Game/Management/GameStateManager.h"
#include "../../../include/Game/Management/TileManager.h"
#include "../../../include/Game/Entities/Monsters/Boar.h"
#include "../../../include/Game/Entities/Monsters/Bee.h"
#include "../../../include/Game/Entities/Monsters/Snail.h"
#include "../../../include/Game/Entities/Objects/Tree.h"
#include "../../../include/Game/Entities/Objects/Coin.h"
#include "../../../include/Game/Entities/Objects/Platform.h"
#include <utility>

Level::Level(LevelDef def) : def_(std::move(def)) {}

/**
 * @brief Turns one parsed spawn record into a live game object.
 *
 * Unknown types are logged and skipped rather than aborting - a typo in a level
 * file should cost one entity, not the whole level.
 */
void Level::ApplySpawn(GameStateManager* gameState, const EntitySpawn& spawn) {
    const std::string& t = spawn.type;

    if (t == "player") {
        auto player = std::make_unique<Player>();
        player->SetPosition({spawn.x, spawn.y});
        gameState->AddObject(std::move(player));
    }
    else if (t == "goal") {
        // Not an entity - a region the player has to reach to finish the level.
        gameState->SetGoal(Rectangle{spawn.x, spawn.y, spawn.w, spawn.h});
    }
    else if (t == "boar") {
        gameState->AddObject(std::make_unique<Boar>(spawn.x, spawn.y, spawn.w, spawn.h, MonsterState::DEFAULT));
    }
    else if (t == "bee") {
        gameState->AddObject(std::make_unique<Bee>(spawn.x, spawn.y, spawn.w, spawn.h, MonsterState::DEFAULT));
    }
    else if (t == "snail") {
        gameState->AddObject(std::make_unique<Snail>(spawn.x, spawn.y, spawn.w, spawn.h, MonsterState::DEFAULT));
    }
    else if (t == "tree") {
        gameState->AddObject(std::make_unique<Tree>(spawn.x, spawn.y, GREEN_TREE_TEXTURE));
    }
    else if (t == "coin") {
        gameState->AddObject(std::make_unique<Coin>(spawn.x, spawn.y));
    }
    else if (t == "platform") {
        gameState->AddObject(std::make_unique<Platform>(spawn.x, spawn.y, spawn.w, spawn.h, BLACK));
    }
    else {
        TraceLog(LOG_WARNING, "[LEVEL] unknown entity type '%s' - skipped", t.c_str());
    }
}

/**
 * @brief Builds the level and returns the populated game state.
 */
GameStateManager* Level::Build() const {
    // Start from a clean state - the manager owns every entity, the tiles and
    // the camera, so reusing it would stack this level on top of the last one.
    GameStateManager::Reset();
    auto* gameState = GameStateManager::GetInstance();

    TraceLog(LOG_INFO, "[LEVEL] building '%s'", def_.name.c_str());

    // Geometry.
    auto tileManager = std::make_unique<TileManager>(Vector2{0, 0});
    const auto tileMap = LevelLoader::LoadLevel(LevelLoader::ResolvePath(def_.tilemapPath));
    tileManager->CreateTiles(tileMap);
    gameState->SetTileManager(std::move(tileManager));

    // Spawns.
    const auto spawns = LevelLoader::LoadEntities(def_.entitiesPath);
    for (const auto& spawn : spawns) {
        ApplySpawn(gameState, spawn);
    }

    if (gameState->GetPlayers().empty()) {
        TraceLog(LOG_ERROR, "[LEVEL] '%s' has no player spawn - the level is unplayable",
                 def_.name.c_str());
    }

    return gameState;
}

Level::~Level() = default;
