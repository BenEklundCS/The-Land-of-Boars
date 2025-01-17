//
// Created by ben on 8/4/24.
//
#include "../../../include/Game/Level/LevelLoader.h"
#include "raylib.h"

/**
 * @brief Loads a level from a specified file path and returns a 2D tile map.
 *
 * The function reads a text file where each line represents a row of tiles.
 * Each character in a line is converted to an integer representing a tile type.
 * The resulting 2D vector represents the tile map for the level.
 *
 * @param filePath The path to the level file.
 * @return std::vector<std::vector<int>> A 2D vector containing the tile map.
 *         Each integer in the vector represents a tile type.
 */
std::vector<std::vector<int>> LevelLoader::LoadLevel(const std::string &filePath) {
    std::vector<std::vector<int>> tileMap;

    // Check if file is open
    if (std::ifstream file(filePath); file.is_open()) {
        std::string line;
        // Read each line of the file
        while (std::getline(file, line)) {
            // Current row vector
            std::vector<int> row;
            // Reach each tile character from the file
            for (const char c : line) {
                int tileType = c - '0'; // Convert char to int
                // Append to the current row
                row.push_back(tileType);
            }
            // Push back the current row into the tileMap
            tileMap.push_back(row);
        }
        file.close();
    }
    // If file is not open, log an error
    else {
        TraceLog(LOG_ERROR, "Unable to open file: %s", filePath.c_str());
    }
    return tileMap;
}

void LevelLoader::SaveLevel(const std::vector<std::vector<std::unique_ptr<Tile>>> &tiles, const std::string &filePath) {
    // Check if the file is open
    if (std::ofstream file(filePath); file.is_open()) {
        // Iterate through each row of tiles
        for (const auto &row : tiles) {
            // Iterate through each tile in the row
            for (const auto &tile : row) {
                // Save tile type as an integer to the file
                if (tile) {
                    file << tile->GetType(); // Assuming Tile has a GetType() method
                } else {
                    file << "0"; // Save 0 for null tiles (or adjust based on your game's logic)
                }
            }
            // Add a newline character after each row
            file << "\n";
        }
        file.close(); // Close the file
    }
    // If file cannot be opened, log an error
    else {
        TraceLog(LOG_ERROR, "Unable to save to file: %s", filePath.c_str());
    }
}





