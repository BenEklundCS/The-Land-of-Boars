//
// Created by luke4 on 11/23/2024.
//

#ifndef ENGINECOMMANDS_H
#define ENGINECOMMANDS_H

#include "Command.h"

#include "../../../Platform/LevelEditor/LevelEditor.h"

class EditLevelCommand : public Command {
public:
    static void Execute(LevelEditor* levelEditor);
};

#endif //ENGINECOMMANDS_H
