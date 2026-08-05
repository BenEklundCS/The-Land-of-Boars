//
// Created by ben on 8/4/24.
//
#include "../../../include/Game/Level/LevelLoader.h"
#include "raylib.h"
#include <sstream>

/**
 * @brief Resolves a repo-relative path against the plausible working directories.
 */
std::string LevelLoader::ResolvePath(const std::string& relativePath) {
    const std::string candidates[] = {
        relativePath,              // launched from the repo root
        "../" + relativePath,      // launched from build/ or cmake-build-debug/
        "../../" + relativePath,   // launched from a nested build config dir
    };
    for (const auto& candidate : candidates) {
        if (std::ifstream probe(candidate); probe.good()) {
            return candidate;
        }
    }
    TraceLog(LOG_WARNING, "Could not resolve asset path: %s", relativePath.c_str());
    return relativePath;
}

/**
 * @brief Parses a level's entity file into spawn records.
 */
std::vector<EntitySpawn> LevelLoader::LoadEntities(const std::string& filePath) {
    std::vector<EntitySpawn> spawns;
    const std::string resolved = ResolvePath(filePath);

    std::ifstream file(resolved);
    if (!file.is_open()) {
        TraceLog(LOG_ERROR, "Unable to open entity file: %s", resolved.c_str());
        return spawns;
    }

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        ++lineNumber;
        // Skip blanks and comments.
        if (line.empty() || line[0] == '#') continue;

        std::istringstream stream(line);
        EntitySpawn spawn;
        if (!(stream >> spawn.type)) continue;

        // Numeric fields are all optional; whichever are present get filled.
        stream >> spawn.x >> spawn.y >> spawn.w >> spawn.h;
        stream.clear();
        stream >> spawn.arg;

        spawns.push_back(spawn);
    }
    file.close();

    TraceLog(LOG_INFO, "[LEVEL] parsed %d entity spawns from %s",
             static_cast<int>(spawns.size()), resolved.c_str());
    return spawns;
}

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





