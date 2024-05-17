#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"
#include "Entities/Platform.h"

int main() {
    Window::GetInstance(); // init the window with GetInstance
    Renderer renderer;

    auto player = new Player();

    LevelScene scene(player);
    scene.AddObject(player);

    auto rectangle1 = new Platform(0, GetScreenHeight() - 100, GetScreenWidth(), 100, DARKBROWN);
    auto rectangle2 = new Platform(550, GetScreenHeight() - 450, 500, 50, BLACK);
    auto rectangle3 = new Platform(1110, GetScreenHeight() - 900, 500, 50, BLACK);

    scene.AddObject(rectangle1);
    scene.AddObject(rectangle2);
    scene.AddObject(rectangle3);

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }

    delete player;
    return 0;
}
