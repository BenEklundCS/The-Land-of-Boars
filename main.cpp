#include <cstdlib>
#include "Level/LevelOne.h"

int main() {

    Window* window = Window::GetInstance();

    LevelOne levelOne = LevelOne();

    levelOne.StartLevel();

    exit(EXIT_SUCCESS);

}
