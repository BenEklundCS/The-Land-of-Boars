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

enum SoundKey {
    HERO_THEME,
    HERO_LANDING,
    HERO_JUMP1,
    HERO_JUMP2,
    HERO_ATTACK,
    BOAR_HIT,
    BOAR_OINK,
    BOAR_DEATH
};

class SoundManager : public Observer {
private:
    static std::unique_ptr<SoundManager> instance;
    std::map<SoundKey, Sound> sounds_;
    void LoadSounds();
public:
    static SoundManager* GetInstance(); // using singleton to avoid loading more sounds than needed into memory
    void PlaySound(SoundKey sound);
    void OnNotify(const GameObject* entity, Events event) override;
};

#endif //PLATFORMER_SOUNDMANAGER_H
