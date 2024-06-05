//
// Created by ben on 6/4/24.
//

#include "../../include/Platform/DebugGUI.h"

void DebugGUI::InitGui() {
    rlImGuiSetup(true);
}

void DebugGUI::DrawGui(GameStateManager *gameState) {
    int player_one = 0;
    playerDataStruct* playerData = gameState->GetPlayerData(player_one);

    // Start imgui frame
    rlImGuiBegin();

    // Render imgui
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");
    bool open = true;
    ImGui::ShowDemoWindow(&open);
    ImGui::End();

    // End imgui frame
    rlImGuiEnd();
}