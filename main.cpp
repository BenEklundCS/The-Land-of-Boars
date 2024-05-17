#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"

int main() {
    Window::GetInstance(); // init the window with GetInstance
    Renderer renderer;
    LevelScene scene;

    auto player = new Player();
    scene.AddObject(player);

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }

    delete player;
    return 0;
}
