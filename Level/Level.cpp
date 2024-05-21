//
// Created by ben on 5/20/24.
//

#include "Level.h"

void Level::Init() {
    player = new Player();
}

void Level::Run() {

}

void Level::Cleanup() {
    delete player;
}
