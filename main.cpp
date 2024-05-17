#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"


int main() {
    Renderer renderer;
    LevelScene scene;

    Player* player = new Player(Vector2{100, 100}, Vector2{100, 100}, RED);
    scene.AddObject(player);

    while (!WindowShouldClose()) {
        scene.Update();
        scene.Draw(renderer);
    }

    delete player;
    return 0;
}