//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "input_reader.h"

#include <utility>

namespace Harpia {
    InputReader::InputReader(std::map<SDL_Keycode, KeyState> *keyState, std::function<void(SDL_Keycode)> onNewKey) {
        _keyState = keyState;
        _onNewKey = std::move(onNewKey);
    }

    bool InputReader::GetKeyDown(SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.down;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyUp(SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.up;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyIsDown(SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.isDown;
        }
        _onNewKey(key);
        return false;
    }


}// namespace Harpia