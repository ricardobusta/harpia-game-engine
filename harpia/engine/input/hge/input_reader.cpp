//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "input_reader.h"
#include <utility>

namespace Harpia {
    InputReader::InputReader(MouseState *mouseState, std::map<KeyCode, KeyState> *keyState, std::function<void(KeyCode)> onNewKey) {
        _keyState = keyState;
        _onNewKey = std::move(onNewKey);
        _mouseState = mouseState;
    }

    bool InputReader::GetKeyDown(const KeyCode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.down;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyUp(const KeyCode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.up;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetKeyIsDown(const KeyCode key) const {
        if (auto it{_keyState->find(key)}; it != _keyState->end()) {
            return it->second.isDown;
        }
        _onNewKey(key);
        return false;
    }

    bool InputReader::GetMouseButtonDown(const MouseButton button) const {
        return _mouseState->mouseButton[static_cast<int>(button)].down;
    }

    bool InputReader::GetMouseButtonUp(const MouseButton button) const {
        return _mouseState->mouseButton[static_cast<int>(button)].up;
    }

    bool InputReader::GetMouseButtonIsDown(const MouseButton button) const {
        return _mouseState->mouseButton[static_cast<int>(button)].isDown;
    }

    const Vector2Int &InputReader::GetMousePos() const {
        return _mouseState->pos;
    }

    const Vector2Int &InputReader::GetMouseWheelDelta() const {
        return _mouseState->wheelDelta;
    }

    int InputReader::GetButtonAxis(KeyCode positive, KeyCode negative) const {
        return (int) GetKeyIsDown(positive) - (int) GetKeyIsDown(negative);
    }
}// namespace Harpia