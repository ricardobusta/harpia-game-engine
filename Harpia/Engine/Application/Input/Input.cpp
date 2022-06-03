//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "Input.h"

#include <SDL.h>
#include "Configuration.h"
#include "Debug.h"

namespace Harpia {
    int Input::Initialize(Configuration *configuration) {
        _keyMap.clear();
        for (int key: *configuration->mappedKeys) {
            DebugLog("[Input] Adding key %d to map", key);
            _keyMap[key] = KeyState();
        }
        return 0;
    }

    void Input::CleanKeyState() {
        for (int key: _dirtyKeys) {
            _keyMap[key].down = false;
            _keyMap[key].up = false;

            auto it = _keyMap.find(key);
        }
        _dirtyKeys.clear();
    }

    void Input::OnKeyUp(SDL_Event *e) {
        auto it = _keyMap.find(e->key.keysym.sym);
        if (it != _keyMap.end()) {
            it->second.isDown = false;
            it->second.up = true;
            _dirtyKeys.push_back(e->key.keysym.sym);
        }
    }

    void Input::OnKeyDown(SDL_Event *e) {
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