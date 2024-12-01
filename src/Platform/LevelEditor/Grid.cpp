//
// Created by luke4 on 11/23/2024.
//

#include "../../../include/Platform/LevelEditor/Grid.h"

#include <raylib.h>

void Grid::DrawGrid() {
    for (int x = -10000; x < 10000; x += 60) {
        DrawLine(x, -10000, x, 10000, BLUE); // Draw vertical lines
    }
    for (int y = -10000; y < 10000; y += 60) {
        DrawLine(-10000, y, 10000, y, BLUE); // Draw horizontal lines
    }
}
