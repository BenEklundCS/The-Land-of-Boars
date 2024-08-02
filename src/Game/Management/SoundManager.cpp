//
// Created by ben on 7/25/24.
//

#include "../../../include/Game/Management/SoundManager.h"

std::unique_ptr<SoundManager> SoundManager::instance = nullptr;

SoundManager *SoundManager::GetInstance() {
    if (instance == nullptr) {
        instance = std::make_unique<SoundManager>();
        instance->LoadSounds();
    }
    return instance.get();
}

void SoundManager::OnNotify(const GameObject *entity, Events event) {
    TraceLog(LOG_INFO, "SoundManager got a notification!");
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