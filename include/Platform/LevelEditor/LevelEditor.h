//
// Created by luke4 on 11/23/2024.
//

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <string>
#include "Grid.h"
#include "raylib.h"

class LevelEditor {
public:
    LevelEditor();
    void EditLevel();
    void LoadLevel();
    void SaveLevel();
    void PlaceTile(Vector2 mousePosition);
    void RemoveTile(Vector2 mousePosition);
};

#endif //LEVELEDITOR_H
