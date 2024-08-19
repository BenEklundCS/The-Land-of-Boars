//
// Created by ben on 8/4/24.
//
#include "../../../include/Game/Level/LevelLoader.h"
#include "raylib.h"

// Load a level from a file
std::vector<std::vector<int>> LevelLoader::LoadLevel(const std::string &filePath) {
    std::vector<std::vector<int>> tileMap;
    std::ifstream file(filePath);

    // Check if file is open
    if (file.is_open()) {
        std::string line;
        // Read each line of the file
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char c : line) {
                int tileType = c - '0'; // Convert char to int
                row.push_back(tileType);
            }
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

