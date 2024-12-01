//
// Created by luke4 on 11/23/2024.
//

#include "../../../../include/Game/Events/Commands/EngineCommands.h"

void EditLevelCommand::Execute(LevelEditor* levelEditor) {
    levelEditor->EditLevel();
}
