#include <cstdlib>
#include "Level/LevelOne.h"

int main() {

    Window* window = Window::GetInstance();

    LevelOne levelOne = LevelOne();

    levelOne.Init();
    levelOne.Run();

    return EXIT_SUCCESS;

}
