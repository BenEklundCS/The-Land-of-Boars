//
// Created by ben on 7/25/24.
//

#ifndef PLATFORMER_SOUNDMANAGER_H
#define PLATFORMER_SOUNDMANAGER_H

#include <map>
#include <string>
#include "raylib.h"
#include <memory>
#include "../Events/Observers/Observer.h"

/**
 * @file SoundManager.h
 * @brief Manages game audio, including sound effect playback and handling sound events.
 *
 * The `SoundManager` is implemented as a singleton to ensure centralized sound management
 * and efficient memory usage by avoiding redundant sound loading.
 */

/**
 * @enum SoundKey
 * @brief Enum for identifying and managing sound effects.
 *
 * Each enum value represents a specific sound effect or theme in the game.
 */
enum SoundKey {
    HERO_THEME,
    HERO_LANDING,
    HERO_JUMP1,
    HERO_JUMP2,
    HERO_ATTACK,
    HERO_HIT,
    HERO_DIED,
    BOAR_HIT,
    BOAR_OINK,
    BOAR_DEATH
};

/**
 * @class SoundManager
 * @brief Handles loading, storing, and playing sound effects.
 *
 * The `SoundManager` observes game events and plays appropriate sounds in response to these events.
 * It follows the singleton pattern for centralized sound handling.
 */
class SoundManager : public Observer {
private:
    static std::unique_ptr<SoundManager> instance; ///< Singleton instance of `SoundManager`.
    std::map<SoundKey, Sound> sounds_; ///< Map of sound effects keyed by `SoundKey`.

    /**
     * @brief Loads all sound effects into memory.
     *
     * This method is called internally to populate the `sounds_` map with audio files.
     */
    void LoadSounds();

public:
    /**
     * @brief Gets the singleton instance of the `SoundManager`.
     * @return Pointer to the `SoundManager` instance.
     *
     * If the instance doesn't exist, it will be created.
     */
    static SoundManager* GetInstance();

    /**
     * @brief Plays the specified sound effect.
     * @param sound The `SoundKey` identifying the sound to play.
     */
    void PlaySound(SoundKey sound);

    /**
     * @brief Handles game events and plays sounds in response.
     * @param entity Pointer to the game object associated with the event.
     * @param event The specific event that occurred.
     *
     * Overrides the `OnNotify` method of the `Observer` class.
     */
    void OnNotify(const GameObject* entity, Events event) override;
};

#endif //PLATFORMER_SOUNDMANAGER_H
