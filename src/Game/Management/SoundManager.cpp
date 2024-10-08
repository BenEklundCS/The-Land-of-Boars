//
// Created by ben on 7/25/24.
//

#include "../../../include/Game/Management/SoundManager.h"

std::unique_ptr<SoundManager> SoundManager::instance = nullptr;

SoundManager *SoundManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<SoundManager>();
        instance->LoadSounds();
        instance->PlaySound(HERO_THEME); // start main game theme!
    }
    return instance.get();
}

void SoundManager::OnNotify(const GameObject *entity, Events event) {
    switch (event) {
        case EVENT_PLAYER_JUMPED:
            // Play jump2 more rarely as it's a grunt/more annoying sound
            if ((rand() % 4) + 1 == 1) {
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

void SoundManager::LoadSounds() {
    // Load a sound and store it in the sounds_ map with its name as the key
    // Main theme
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_THEME, LoadSound("../Assets/Sounds/heroTheme.wav")));
    // Player sounds
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_LANDING, LoadSound("../Assets/Sounds/jumpland.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_JUMP1, LoadSound("../Assets/Sounds/jumpSound1.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_JUMP2, LoadSound("../Assets/Sounds/jumpSound2.mp3")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_ATTACK, LoadSound("../Assets/Sounds/swing.wav")));
    // Boar sounds
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_HIT, LoadSound("../Assets/Sounds/boarHit.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_OINK, LoadSound("../Assets/Sounds/boarOink.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(BOAR_DEATH, LoadSound("../Assets/Sounds/boarDeath.wav")));
}

void SoundManager::PlaySound(SoundKey sound) {
    if (sounds_.find(sound) != sounds_.end())
        ::PlaySound(sounds_.at(sound));
}

