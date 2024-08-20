//
// Created by ben on 6/4/24.
//

#include "../../include/Platform/DebugGUI.h"

void DebugGUI::InitGui() {
    TraceLog(LOG_INFO, "Setting up ImGui");
    rlImGuiSetup(true);
    TraceLog(LOG_INFO, "ImGui setup complete");
}

std::string ColorToString(Color color) {
    return "(r: " + std::to_string(color.r) +
           ", g: " + std::to_string(color.g) +
           ", b: " + std::to_string(color.b) +
           ", a: " + std::to_string(color.a) + ")";
}

std::string PlayerStateToString(PlayerState state) {
    std::string stateString;
    // Parse the state
    if (state == IDLE) {
        stateString = "IDLE";
    }
    else if (state == RUNNING) {
        stateString = "RUNNING";
    }
    else if (state == JUMPING ){
        stateString = "JUMPING";
    }
    else {
        stateString = "ATTACKING";
    }
    return stateString;
}

void DebugGUI::DrawGui(GameStateManager *gameState) {
    gameData gameData = gameState->GetGameData();

    rlImGuiBegin();
    // show ImGui Content
    ImGui::SetWindowFontScale(2);
    // Render player data
    ImGui::Text("Player data:");
    ImGui::Text("Position: %1.2fx, %1.2fy", gameData.player->GetPosition().x, gameData.player->GetPosition().y);
    ImGui::Text("Velocity: %1.2fx, %1.2fy", gameData.player->GetVelocity().x, gameData.player->GetVelocity().y);
    // Render player data
    ImGui::Text("Health: %d", gameData.player->GetPlayerData()->hp_);
    ImGui::Text("Jumps: %d", gameData.player->GetPlayerData()->jumps_);
    // Render player state
    ImGui::Text("State: %s", PlayerStateToString(gameData.player->GetPlayerData()->state_).c_str());
    ImGui::Text("isOnGround: %s", (gameData.player->GetPlayerData()->isOnGround_) ? "True" : "False");
    ImGui::Text("timeSinceHit: %1.2f", gameData.player->GetPlayerData()->timeSinceHit_);
    ImGui::Text("");
    // Number of objects
    ImGui::Text("Object counts:");
    ImGui::Text("Player count: %zu", gameData.numPlayers);
    ImGui::Text("Monsters count: %zu", gameData.numMonsters);
    ImGui::Text("Platforms count: %zu", gameData.numPlatforms);
    ImGui::Text("Other count: %zu", gameData.numOther);
    // Submit ImGui data to Raylib for processing
    rlImGuiEnd();
}