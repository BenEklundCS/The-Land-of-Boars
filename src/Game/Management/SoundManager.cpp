//
// Created by ben on 7/25/24.
//

#include "../../../include/Game/Management/SoundManager.h"
#include "../../../include/Utilities/Random.h"

std::unique_ptr<SoundManager> SoundManager::instance = nullptr;


/**
 * @brief Retrieves the singleton instance of the SoundManager.
 *
 * If the instance does not already exist, it is created and initialized with
 * loaded sounds. The main game theme is also started upon the first call.
 *
 * @return SoundManager* A pointer to the singleton instance.
 */
SoundManager *SoundManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<SoundManager>();
        instance->LoadSounds();
        instance->PlaySound(HERO_THEME); // start main game theme!
    }
    return instance.get();
}

/**
 * @brief Responds to game events and plays the appropriate sound.
 *
 * This function is called whenever the SoundManager is notified of a game event.
 * It determines the correct sound to play based on the event type and, for some
 * events, introduces randomness for variety.
 *
 * @param entity A pointer to the game object triggering the event (unused).
 * @param event The event type triggering the notification.
 */
void SoundManager::OnNotify(const GameObject *entity, Events event) {
    switch (event) {
        case EVENT_PLAYER_JUMPED:
            // Play jump2 more rarely as it's a grunt/more annoying sound
            if (GetRandomInt(1, 4) == 1) {
                PlaySound(HERO_JUMP2);
            } else { // play the basic jump sound if the rand doesn't hit
                PlaySound(HERO_JUMP1);
            }
            break;
        case EVENT_PLAYER_ATTACK:
            PlaySound(HERO_ATTACK);
            break;
        case EVENT_PLAYER_LANDED:
            PlaySound(HERO_LANDING);
            break;
        case EVENT_PLAYER_HIT:
            PlaySound(HERO_HIT);
            break;
        case EVENT_PLAYER_DIED:
            PlaySound(HERO_DIED);
            break;
        case EVENT_BOAR_HIT:
            PlaySound(BOAR_HIT);
            break;
        case EVENT_BOAR_OINKED:
            PlaySound(BOAR_OINK);
            break;
        case EVENT_BOAR_DIED:
            PlaySound(BOAR_DEATH);
            break;
        default:
            TraceLog(LOG_INFO, "SoundManager notified of unknown event: %d", event);
            break;
    }
}

/**
 * @brief Loads all game sounds and stores them in a map for quick access.
 *
 * This function initializes the `sounds_` map by associating `SoundKey` enums
 * with their corresponding loaded sound files. All sounds are preloaded to
 * ensure smooth playback during the game.
 */
void SoundManager::LoadSounds() {
    // Load a sound and store it in the sounds_ map with its name as the key
    // Main theme
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_THEME, LoadSound("../Assets/Sounds/heroTheme.wav")));
    // Player sounds
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_LANDING, LoadSound("../Assets/Sounds/jumpland.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_JUMP1, LoadSound("../Assets/Sounds/jumpSound1.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_JUMP2, LoadSound("../Assets/Sounds/jumpSound2.mp3")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_ATTACK, LoadSound("../Assets/Sounds/swing.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_HIT, LoadSound("../Assets/Sounds/impact-of-blow.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_DIED, LoadSound("../Assets/Sounds/player-death.mp3")));
    // Boar sounds
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_HIT, LoadSound("../Assets/Sounds/boarHit.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_OINK, LoadSound("../Assets/Sounds/boarOink.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_DEATH, LoadSound("../Assets/Sounds/boarDeath.wav")));
}

/**
 * @brief Plays the specified sound.
 *
 * This function retrieves a sound from the `sounds_` map using its `SoundKey`
 * and plays it. If the sound is not found, no action is taken.
 *
 * @param sound The key corresponding to the sound to play.
 */
void SoundManager::PlaySound(const SoundKey sound) {
    if (sounds_.find(sound) != sounds_.end())
        ::PlaySound(sounds_.at(sound));
}

