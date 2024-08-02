//
// Created by ben on 8/1/24.
//

#ifndef PLATFORMER_SUBJECT_H
#define PLATFORMER_SUBJECT_H

#define MAX_OBSERVERS 4096

#endif //PLATFORMER_SUBJECT_H

#include "Observer.h"

class Subject {
private:
    // This should be a smarter array in final implementation
    Observer* observers_[MAX_OBSERVERS] = {nullptr};
    int numObservers_;
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    ~Subject();
protected:
    void notify(const GameObject* entity, Event event);
};