//
// Created by ben on 5/20/24.
//

#include "../../include/Level/LevelOne.h"
#include "../../include/Entities/Objects/Tile.h"
#include "../../include/Entities/Monsters/Boar.h"

std::unique_ptr<GameStateManager> LevelOne::GetGameState() {
    auto player = std::make_unique<Player>();
    auto gameState = std::make_unique<GameStateManager>();

    gameState->AddObject(std::move(player));

    auto platform1 = std::make_unique<Platform>(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto platform2 = std::make_unique<Platform>(550, (float)GetScreenHeight() - 400, 500, 50, BLACK);
    auto platform3 = std::make_unique<Platform>(1300, (float)GetScreenHeight() - 700, 500, 50, BLACK);
    auto platform4 = std::make_unique<Platform>(550, 300, 500, 50, BLACK);

    auto tile = std::make_unique<Tile>(100, 100);
    gameState->AddObject(std::move(tile));

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
