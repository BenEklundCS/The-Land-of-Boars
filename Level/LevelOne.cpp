//
// Created by ben on 5/20/24.
//

#include "LevelOne.h"

void LevelOne::Run() {
    LevelScene scene(player);

    scene.AddObject(player);

    auto platform1 = new Platform(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto platform2 = new Platform(550, (float)GetScreenHeight() - 450, 500, 50, BLACK);
    auto platform3 = new Platform(1110, (float)GetScreenHeight() - 900, 500, 50, BLACK);

    scene.AddObject(platform1);
    scene.AddObject(platform2);
    scene.AddObject(platform3);

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }

    delete platform1;
    delete platform2;
    delete platform3;
}
