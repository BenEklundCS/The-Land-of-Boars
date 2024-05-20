#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"
#include "Entities/Platform.h"
#include "Sprites/TextureManager.h"

int main() {
    Window* window = Window::GetInstance(); // init the window with GetInstance
    TextureManager::LoadTextures();

    Renderer renderer;

    auto player = new Player();

    LevelScene scene(player);

    scene.AddObject(player);

    auto rectangle1 = new Platform(0, (float)GetScreenHeight() - 100, (float)GetScreenWidth(), 100, DARKBROWN);
    auto rectangle2 = new Platform(550, (float)GetScreenHeight() - 450, 500, 50, BLACK);
    auto rectangle3 = new Platform(1110, (float)GetScreenHeight() - 900, 500, 50, BLACK);

    scene.AddObject(rectangle1);
    scene.AddObject(rectangle2);
    scene.AddObject(rectangle3);

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }

    // Delete objects
    delete player;
    delete window;
    delete rectangle1;
    delete rectangle2;
    delete rectangle3;

    return 0;
}
