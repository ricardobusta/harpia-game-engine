//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "InputReader.h"
#include "Debug.h"

namespace Harpia {
    InputReader::InputReader(std::map<SDL_Keycode, KeyState> *keyState) {
        _keyState = keyState;
    }

    bool InputReader::GetKeyDown(SDL_Keycode key) {
        if (auto it{_keyState->find(key)};it != _keyState->end()) {
            return it->second.down;
        }
        DebugLogWarning("Key %d not mapped", key);
        return false;
    }

    bool InputReader::GetKeyUp(SDL_Keycode key) {
        if (auto it{_keyState->find(key)};it != _keyState->end()) {
            return it->second.up;
        }
        DebugLogWarning("Key %d not mapped", key);
        return false;
    }

    bool InputReader::GetKeyIsDown(SDL_Keycode key) {
        if (auto it{_keyState->find(key)};it != _keyState->end()) {
            return it->second.isDown;
        }
        DebugLogWarning("Key %d not mapped", key);
        return false;
    }


} // Harpia