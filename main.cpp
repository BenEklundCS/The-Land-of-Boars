#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"
#include "Entities/Platform.h"
#include "Sprites/TextureManager.h"

int main() {
    Window* window = Window::GetInstance(); // init the window with GetInstance

    Renderer renderer;

    auto player = new Player();

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

    // Delete objects
    delete player;
    delete window;
    delete platform1;
    delete platform2;
    delete platform3;

    return 0;
}
