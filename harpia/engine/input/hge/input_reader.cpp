//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "input_reader.h"
#include <utility>

namespace Harpia {
    InputReader::InputReader(MouseState *mouseState, std::map<SDL_Keycode, KeyState> *keyState, std::function<void(SDL_Keycode)> onNewKey) {
        _keyState = keyState;
        _onNewKey = std::move(onNewKey);
        _mouseState = mouseState;
    }

    bool InputReader::GetKeyDown(const SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.down;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyUp(const SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.up;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyIsDown(const SDL_Keycode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.isDown;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetMouseButtonDown(const int index) const {
        return _mouseState->mouseButton[index].down;
    }

    bool InputReader::GetMouseButtonUp(const int index) const {
        return _mouseState->mouseButton[index].up;
    }

    bool InputReader::GetMouseButtonIsDown(const int index) const {
        return _mouseState->mouseButton[index].isDown;
    }

    const Vector2Int &InputReader::GetMousePos() const {
        return _mouseState->pos;
    }

    const Vector2Int &InputReader::GetMouseWheelDelta() const {
        return _mouseState->wheelDelta;
    }

    int InputReader::GetButtonAxis(SDL_KeyCode positive, SDL_KeyCode negative) const {
        return (int) GetKeyIsDown(positive) - (int) GetKeyIsDown(negative);
    }
}// namespace Harpia