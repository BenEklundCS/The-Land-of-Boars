#include "raylib.h"
#include "Window.h"

int main() {
    // Initialization
    Window window = Window(WINDOW_WIDTH, WINDOW_HEIGHT);

    SetTargetFPS(60); // Set the desired frames per second

    // Main game loop
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        // Update (Not necessary for this simple example)

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE); // Set the background color

        DrawText("Hello from raylib in C++!", 190, 200, 20, LIGHTGRAY); // Draw some text

        EndDrawing();
    }

    // De-initialization
    CloseWindow(); // Close window and OpenGL context

    return 0;
}
