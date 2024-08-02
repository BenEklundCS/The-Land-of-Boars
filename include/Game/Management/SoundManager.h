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

class SoundManager : public Observer {
private:
    static std::unique_ptr<SoundManager> instance;
    std::map<std::string, Sound> sounds;
    void LoadSounds();
public:
    static SoundManager* GetInstance(); // using singleton to avoid loading more sounds than needed into memory
    void PlaySound(std::string sound_name);
    void OnNotify(const GameObject* entity, Events event) override;
};

#endif //PLATFORMER_SOUNDMANAGER_H
