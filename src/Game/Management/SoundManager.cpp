//
// Created by ben on 7/25/24.
//

#include "../../../include/Game/Management/SoundManager.h"

SoundManager *SoundManager::getInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<SoundManager>();
        instance->LoadSounds();
    }
    return instance.get();
}

void SoundManager::LoadSounds() {

}

void SoundManager::PlaySound(std::string sound_name) {

}