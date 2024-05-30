//
// Created by ben on 5/20/24.
//

#include "../../include/Level/LevelOne.h"
#include "../../include/Entities/Objects/Tile.h"
#include "../../include/Entities/Monsters/Boar.h"

Scene* LevelOne::GetScene() {
    Player* player = new Player();

    Scene* scene = new Scene();

    scene->AddObject(player);

    auto platform1 = new Platform(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto platform2 = new Platform(550, (float)GetScreenHeight() - 400, 500, 50, BLACK);
    auto platform3 = new Platform(1300, (float)GetScreenHeight() - 700, 500, 50, BLACK);
    auto platform4 = new Platform(550, 300, 500, 50, BLACK);

    auto tile = new Tile(100, 100);
    scene->AddObject(tile);

    scene->AddObject(platform1);
    scene->AddObject(platform2);
    scene->AddObject(platform3);
    scene->AddObject(platform4);

    auto monster1 = new Boar(1000, 200, 100, 100, MonsterState::PACING);
    auto monster2 = new Boar(2000, GetScreenHeight()-200, 100, 100, MonsterState::DEFAULT);

    scene->AddObject(monster1);
    scene->AddObject(monster2);

    return scene;
}
