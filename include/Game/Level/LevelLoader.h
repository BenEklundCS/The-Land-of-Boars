//
// Created by ben on 8/4/24.
//

#ifndef PLATFORMER_LEVELLOADER_H
#define PLATFORMER_LEVELLOADER_H

#include <fstream>
#include <vector>
#include <string>

class LevelLoader {
public:
    std::vector<std::vector<int>> LoadLevel(const std::string& filePath);
};

#endif //PLATFORMER_LEVELLOADER_H
