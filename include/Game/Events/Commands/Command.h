//
// Created by ben on 7/31/24.
//

#ifndef PLATFORMER_COMMAND_H
#define PLATFORMER_COMMAND_H

class Command {
public:
    virtual ~Command() = default;
    virtual void Execute() = 0;
};

#endif //PLATFORMER_COMMAND_H
