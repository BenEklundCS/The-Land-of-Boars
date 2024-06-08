//
// Created by ben on 6/4/24.
//

#include "../../include/Platform/DebugGUI.h"

void DebugGUI::InitGui() {
    rlImGuiSetup(true);
}

void DebugGUI::DrawGui(GameStateManager *gameState) {
    int player_one = 0;
    const gameData* gameData = gameState->GetGameData();
    const playerDataStruct* playerData = gameData->playerData;
    rlImGuiBegin();
    // show ImGui Content
    //bool open = true;
    //ImGui::ShowDemoWindow(&open);
    ImGui::SetWindowFontScale(2);
    ImGui::Text("playerData:");
    ImGui::Text("");
    ImGui::Text("Position: %fx, %fy", gameData->playerPosition.x, gameData->playerPosition.y);
    ImGui::Text("Velocity: %fx, %fy", playerData->velocity_.x, playerData->velocity_.y);
    ImGui::Text("Color: %d", ColorToInt(playerData->color_));
    ImGui::Text("Health: %d", playerData->hp_);
    ImGui::Text("Jumps: %d", playerData->jumps_);
    // Render player state
    PlayerState state = playerData->state_;
    std::string stateString;
    // Parse the state
    if (state == IDLE) {
        stateString = "IDLE";
    }
    else if (state == RUNNING) {
        stateString = "RUNNING";
    }
    else {
        stateString = "JUMPING";
    }
    ImGui::Text("State: %s", stateString.c_str());
    ImGui::Text("timeSinceHit: %f", playerData->timeSinceHit_);
    rlImGuiEnd();

    delete gameData;

}