//
// Created by ben on 6/4/24.
//

#include "../../include/Platform/GUI.h"

// Initialize static members
int GUI::blockSelection_ = 0;

/**
 * @brief Initialize ImGui for debugging purposes.
 */
void GUI::InitGui() {
    TraceLog(LOG_INFO, "Setting up ImGui");
    rlImGuiSetup(true);
    TraceLog(LOG_INFO, "ImGui setup complete");
}

/**
 * @brief Convert a Raylib Color struct to a string representation.
 *
 * @param color The Color struct to convert.
 * @return std::string The string representation of the color.
 */
std::string GUI::ColorToString(const Color color) {
    return "( r: " + std::to_string(color.r) +
           ", g: " + std::to_string(color.g) +
           ", b: " + std::to_string(color.b) +
           ", a: " + std::to_string(color.a) + " )";
}

/**
 * @brief Convert a PlayerState enum to a string representation.
 *
 * @param state The PlayerState to convert.
 * @return std::string The string representation of the player state.
 */
std::string GUI::PlayerStateToString(const PlayerState state) {
    std::string stateString;
    // Parse the state
    if (state == IDLE) {
        stateString = "IDLE";
    }
    else if (state == RUNNING) {
        stateString = "RUNNING";
    }
    else if (state == JUMPING){
        stateString = "JUMPING";
    }
    else {
        stateString = "ATTACKING";
    }
    return stateString;
}

/**
 * @brief Render the Debug GUI for the game.
 *
 * Displays game state and player data using ImGui.
 *
 * @param gameState The current game state manager instance.
 */
void GUI::DrawDebugGUI(const GameStateManager *gameState) {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()));

    auto [player, numPlayers, numMonsters, numPlatforms, numOther] = gameState->GetGameData();

    rlImGuiBegin();
    ImGui::Begin("Debug");
    // show ImGui Content
    ImGui::SetWindowFontScale(2);
    // Render player data
    ImGui::Text("Player data:");
    ImGui::Text("Position: %1.2fx, %1.2fy", player->GetPosition().x, player->GetPosition().y);
    ImGui::Text("Velocity: %1.2fx, %1.2fy", player->GetVelocity().x, player->GetVelocity().y);
    // Render player data
    ImGui::Text("Health: %d", player->GetPlayerData()->hp_);
    ImGui::Text("Jumps: %d", player->GetPlayerData()->jumps_);
    ImGui::Text("Coins: %d", player->GetPlayerData()->coins_);
    // Render player state
    ImGui::Text("State: %s", PlayerStateToString(player->GetPlayerData()->state_).c_str());
    ImGui::Text("isOnGround: %s", (player->GetPlayerData()->isOnGround_) ? "True" : "False");
    ImGui::Text("timeSinceHit: %1.2f", player->GetPlayerData()->timeSinceHit_);
    ImGui::Text("");
    // Number of objects
    ImGui::Text("Object counts:");
    ImGui::Text("Player count: %zu", numPlayers);
    ImGui::Text("Monsters count: %zu", numMonsters);
    ImGui::Text("Platforms count: %zu", numPlatforms);
    ImGui::Text("Other count: %zu", numOther);
    // Submit ImGui data to Raylib for processing
    ImGui::End();
    rlImGuiEnd();
}

/**
 * @brief Renders the level editor GUI giving the user tools to edit the level.
 *
 * The GUI displays:
 * - A block selector, for selecting between air, dirt, and grass blocks for placement in the level.
 */
void GUI::DrawEditorGUI() {
    rlImGuiBegin();
    ImGui::SetNextWindowFocus();
    ImGui::Begin("Editor", nullptr);
    // show ImGui Content
    ImGui::SetWindowFontScale(2);
    // ImGUI button simply checks if it was pressed, and returns True if yes.
    if (ImGui::Button("Air")) {
        TraceLog(LOG_INFO, "User selected AIR BLOCK.");
        blockSelection_ = 0;
    }
    if (ImGui::Button("Dirt")) {
        TraceLog(LOG_INFO, "User selected DIRT BLOCK.");
        blockSelection_ = 1;
    }
    if (ImGui::Button("Grass")) {
        TraceLog(LOG_INFO, "User selected GRASS BLOCK.");
        blockSelection_ = 2;
    }
    ImGui::End();
    rlImGuiEnd();
}

int GUI::GetBlockSelection() {
    return blockSelection_;
}