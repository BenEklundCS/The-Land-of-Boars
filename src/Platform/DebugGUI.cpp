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

    TraceLog(LOG_INFO, "Drawing ImGUI");
    rlImGuiBegin();
    // show ImGui Content
    bool open = true;
    ImGui::ShowDemoWindow(&open);
    rlImGuiEnd();
}