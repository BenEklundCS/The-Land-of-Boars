//
// Created by ben on 7/25/24.
//

#include "../../../include/Game/Management/SoundManager.h"

std::unique_ptr<SoundManager> SoundManager::instance = nullptr;

SoundManager *SoundManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<SoundManager>();
        instance->LoadSounds();
        instance->PlaySound("heroTheme"); // start main game theme!
    }
    return instance.get();
}

void SoundManager::OnNotify(const GameObject *entity, Events event) {
    switch (event) {
        case EVENT_PLAYER_JUMPED:
            PlaySound("jump");
            break;
        case EVENT_PLAYER_ATTACK:
            PlaySound("attack");
            break;
        case EVENT_PLAYER_LANDED:
            PlaySound("landingSound");
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
    sounds_.emplace(std::pair<std::string, Sound>("heroTheme", LoadSound("../Assets/Sounds/heroTheme.wav")));
    sounds_.emplace(std::pair<std::string, Sound>("landingSound", LoadSound("../Assets/Sounds/jumpland.wav")));
    sounds_.emplace(std::pair<std::string, Sound>("jump", LoadSound("../Assets/Sounds/jumpSound.mp3")));
}

void SoundManager::PlaySound(std::string sound_name) {
    if (sounds_.find(sound_name) != sounds_.end())
        ::PlaySound(sounds_.at(sound_name));
}

