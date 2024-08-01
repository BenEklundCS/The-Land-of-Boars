//
// Created by ben on 7/31/24.
//

#ifndef PLATFORMER_COMMAND_H
#define PLATFORMER_COMMAND_H

#endif //PLATFORMER_COMMAND_H

class Command {
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};
