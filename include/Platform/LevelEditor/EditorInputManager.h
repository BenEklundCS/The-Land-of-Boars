//
// Created by luke4 on 11/24/2024.
//

#ifndef EDITORINPUTMANAGER_H
#define EDITORINPUTMANAGER_H

#ifndef EDITOR_INPUT_MANAGER_H
#define EDITOR_INPUT_MANAGER_H

#include "LevelEditor.h"

class EditorInputManager {
public:
    explicit EditorInputManager(LevelEditor* editor);

    void HandleEditorInput();

private:
    LevelEditor* levelEditor_;
};

#endif // EDITOR_INPUT_MANAGER_H


#endif //EDITORINPUTMANAGER_H
