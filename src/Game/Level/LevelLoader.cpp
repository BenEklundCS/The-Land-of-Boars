//
// Created by ben on 8/4/24.
//
#include "../../../include/Game/Level/LevelLoader.h"

std::vector<std::vector<int>> LevelLoader::LoadLevel(const std::string &filePath) {
    std::vector<std::vector<int>> tileMap;
    std::ifstream file(filePath);

    if (file.is_open()) {
        std::string line;
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

    return tileMap;
}

