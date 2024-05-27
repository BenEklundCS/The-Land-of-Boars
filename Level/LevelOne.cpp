//
// Created by ben on 5/20/24.
//

#include "LevelOne.h"

void LevelOne::StartLevel() {
    player = std::make_unique<Player>();

    LevelScene scene;

    scene.AddObject(player.get());

    auto platform1 = std::make_unique<Platform>(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto platform2 = std::make_unique<Platform>(550, (float)GetScreenHeight() - 400, 500, 50, BLACK);
    auto platform3 = std::make_unique<Platform>(1300, (float)GetScreenHeight() - 700, 500, 50, BLACK);
    auto platform4 = std::make_unique<Platform>(550, 300, 500, 50, BLACK);

    scene.AddObject(platform1.get());
    scene.AddObject(platform2.get());
    scene.AddObject(platform3.get());
    scene.AddObject(platform4.get());

    auto monster1 = std::make_unique<Boar>(1000, 200, 100, 100, MonsterState::PACING);
    auto monster2 = std::make_unique<Boar>(2000, GetScreenHeight()-200, 100, 100, MonsterState::DEFAULT);

    for (int i = 0; i < 10000; i++) {
        auto monster = new Boar(1000 + i * 50, 200 + i * 50, 100 , 100, MonsterState::PACING);
        scene.AddObject(monster);
    }

    scene.AddObject(monster1.get());
    scene.AddObject(monster2.get());

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw();
    }
}
