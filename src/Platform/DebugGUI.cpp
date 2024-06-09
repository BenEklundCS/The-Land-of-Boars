//
// Created by ben on 6/4/24.
//

#include "../../include/Platform/DebugGUI.h"

void DebugGUI::InitGui() {
    rlImGuiSetup(true);
}

std::string ColorToString(Color color) {
    return "r: " + std::to_string(color.r) +
           ", g: " + std::to_string(color.g) +
           ", b: " + std::to_string(color.b) +
           ", a: " + std::to_string(color.a) + ")";
}

void DebugGUI::DrawGui(GameStateManager *gameState) {
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
    ImGui::Text("Color: %s", ColorToString(playerData->color_).c_str());
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
    ImGui::Text("isOnGround %b", playerData->isOnGround_);
    ImGui::Text("timeSinceHit: %f", playerData->timeSinceHit_);
    rlImGuiEnd();

    delete gameData;

}