#include <cstdlib>
#include "Renderer/Window.h"
#include "Renderer/Renderer.h"
#include "Level/LevelScene.h"
#include "Entities/Player.h"
#include "Entities/Platform.h"
#include "Level/Level.h"
#include "Level/LevelOne.h"

int main() {

    LevelOne levelOne = LevelOne();

    levelOne.Init();
    levelOne.Run();
    levelOne.Cleanup();

    CloseWindow();

    return EXIT_SUCCESS;
}
