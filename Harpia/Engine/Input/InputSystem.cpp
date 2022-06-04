//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "InputSystem.h"

#include <SDL.h>
#include "Configuration.h"
#include "Debug.h"

namespace Harpia {
    int InputSystem::Initialize(InputConfiguration &configuration) {
        _keyMap.clear();
        for (int key: configuration.mappedKeys) {
            DebugLog("Adding key %d to map", key);
            _keyMap[key] = KeyState();
        }
        return 0;
    }

    void InputSystem::CleanKeyState() {
        for (int key: _dirtyKeys) {
            _keyMap[key].down = false;
            _keyMap[key].up = false;

            auto it = _keyMap.find(key);
        }
        _dirtyKeys.clear();
    }

    void InputSystem::OnKeyUp(SDL_Event *e) {
        auto it = _keyMap.find(e->key.keysym.sym);
        if (it != _keyMap.end()) {
            it->second.isDown = false;
            it->second.up = true;
            _dirtyKeys.push_back(e->key.keysym.sym);
        }
    }

    void InputSystem::OnKeyDown(SDL_Event *e) {
        auto it = _keyMap.find(e->key.keysym.sym);
        if (it == _keyMap.end()) {
            return; // key not mapped
        }
        if (it->second.isDown) {
            return; // key already down
        }
        it->second.down = true;
        it->second.isDown = true;
        _dirtyKeys.push_back(e->key.keysym.sym);
    }
} // Harpia