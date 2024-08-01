//
// Created by ben on 6/4/24.
//

#ifndef PLATFORMER_DEBUGGUI_H
#define PLATFORMER_DEBUGGUI_H


#include "../Game/Management/GameStateManager.h"
#include "raylib.h"
#include "raymath.h"

#include "imgui.h"
#include "rlImGui.h"

class DebugGUI {
public:
    static void InitGui();
    static void DrawGui(StateManager* gameState);
};


#endif //PLATFORMER_DEBUGGUI_H
