#include <cstdlib>
#include "../../include/Platform/Engine.h"

int main() {

    Engine gameEngine = Engine();

    gameEngine.StartGame();

    exit(EXIT_SUCCESS);

}

/*
int main() {
    // Initialize window
    int screenWidth = 1280;
    int screenHeight = 800;

    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "ImGui + Raylib Integration Example");
    SetTargetFPS(60);

    // Initialize ImGui
    rlImGuiSetup(true);

    // Main loop
    while (!WindowShouldClose()) {
        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Begin ImGui frame
        rlImGuiBegin();

        // Show ImGui content
        ImGui::Begin("Test Window");
        ImGui::Text("Hello, world!");
        ImGui::End();

        // Show ImGui Metrics/Debug Window
        ImGui::ShowMetricsWindow();

        // End ImGui frame
        rlImGuiEnd();

        // End drawing
        EndDrawing();
    }

    // Clean up
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
*/