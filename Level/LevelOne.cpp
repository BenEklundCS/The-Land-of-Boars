//
// Created by ben on 5/20/24.
//

#include "LevelOne.h"

void LevelOne::Run() {
    LevelScene scene(player.get());

    scene.AddObject(player.get());

    auto platform1 = std::make_unique<Platform>(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto platform2 = std::make_unique<Platform>(550, (float)GetScreenHeight() - 450, 500, 50, BLACK);
    auto platform3 = std::make_unique<Platform>(1110, (float)GetScreenHeight() - 900, 500, 50, BLACK);

    scene.AddObject(platform1.get());
    scene.AddObject(platform2.get());
    scene.AddObject(platform3.get());

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }
}
