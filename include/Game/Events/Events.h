//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_EVENTS_H
#define PLATFORMER_EVENTS_H

/**
 * @enum Events
 * @brief Enum representing the different types of events that can occur in the game.
 *
 * Events are used to notify Observers about actions or state changes that have occurred
 * during the game. These events allow for a decoupled architecture, where Observers can
 * react to specific game events without direct coupling to the objects that trigger them.
 */
enum Events {
    EVENT_PLAYER_JUMPED,   ///< Triggered when the player successfully jumps.
    EVENT_PLAYER_ATTACK,   ///< Triggered when the player performs an attack.
    EVENT_PLAYER_LANDED,   ///< Triggered when the player lands on the ground after a jump or fall.
    EVENT_PLAYER_HIT,      ///< Triggered when the player takes damage from an enemy or hazard.
    EVENT_PLAYER_DIED,     ///< Triggered when the player loses all health and dies.

    EVENT_BOAR_HIT,        ///< Triggered when a boar is hit by the player or another entity.
    EVENT_BOAR_OINKED,     ///< Triggered when a boar emits an oink sound.
    EVENT_BOAR_DIED,       ///< Triggered when a boar loses all health and dies.

    EVENT_SNAIL_HIT,       ///< Triggered when a snail is hit by the player or another entity.
    EVENT_SNAIL_DIED,      ///< Triggered when a snail loses all health and dies.

    EVENT_BEE_HIT,         ///< Triggered when a bee is hit by the player or another entity.
    EVENT_BEE_DIED,        ///< Triggered when a bee loses all health and dies.

    EVENT_MONSTER_DIED     ///< Triggered at the end of all monster death animations.
};

#endif //PLATFORMER_EVENTS_H
