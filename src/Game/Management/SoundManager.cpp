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

void SoundManager::onNotify(const GameObject *entity, Event event) {
    switch (event) {
        case EVENT_PLAYER_JUMPED:
            TraceLog(LOG_INFO, "SoundManager notified of EVENT_PLAYER_JUMPED");
            return;
        case EVENT_PLAYER_ATTACK:
            TraceLog(LOG_INFO, "SoundManager notified of EVENT_PLAYER_ATTACK");
            return;
    }
}

void SoundManager::LoadSounds() {

}

void SoundManager::PlaySound(std::string sound_name) {

}