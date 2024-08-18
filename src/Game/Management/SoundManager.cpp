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
            PlaySound(HERO_JUMP);
            break;
        case EVENT_PLAYER_ATTACK:
            PlaySound(HERO_ATTACK);
            break;
        case EVENT_PLAYER_LANDED:
            PlaySound(HERO_LANDING);
            break;
        default:
            TraceLog(LOG_INFO, "SoundManager notified of unknown event: %d", event);
            break;
    }
}

void SoundManager::LoadSounds() {
    // Load a sound and store it in the sounds_ map with its name as the key
    //sounds.at("jump") = LoadSound("path_to_your_jump_sound.wav");
    //sounds.at("attack") = LoadSound("path_to_your_attack_sound.wav");
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_THEME, LoadSound("../Assets/Sounds/heroTheme.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_LANDING, LoadSound("../Assets/Sounds/jumpland.wav")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_JUMP, LoadSound("../Assets/Sounds/jumpSound.mp3")));
    sounds_.emplace(std::pair<SoundKey, Sound>(HERO_ATTACK, LoadSound("../Assets/Sounds/rpg_sound_pack/RPG Sound Pack/battle/swing.wav")));
}

void SoundManager::PlaySound(SoundKey sound) {
    if (sounds_.find(sound) != sounds_.end())
        ::PlaySound(sounds_.at(sound));
}

