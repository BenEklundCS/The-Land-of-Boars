//
// Created by ben on 7/31/24.
//

#ifndef PLATFORMER_COMMAND_H
#define PLATFORMER_COMMAND_H

/**
 * @class Command
 * @brief Abstract base class representing a generic command.
 *
 * The `Command` class provides a unified interface for defining commands
 * that encapsulate actions or operations. Derived classes must implement
 * the `Execute` method, which defines the specific behavior of the command.
 *
 * This class is designed to follow the Command Pattern, enabling
 * decoupling between input handling and action execution logic.
 */
class Command {
public:
    /**
     * @brief Virtual destructor for the Command base class.
     *
     * Ensures proper cleanup of derived class resources when a
     * `Command` object is deleted through a base class pointer.
     */
    virtual ~Command() = default;

    /**
     * @brief Pure virtual method that executes the command.
     *
     * This method must be implemented by derived classes to define
     * the specific behavior or action associated with the command.
     */
    virtual void Execute() = 0;
};

#endif //PLATFORMER_COMMAND_H
