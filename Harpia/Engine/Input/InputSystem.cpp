//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "InputSystem.h"

#include <SDL.h>
#include "Configuration.h"
#include "Debug.h"
#include "CoreSystem.h"

namespace Harpia {
    //region public
    int InputSystem::Initialize(InputConfiguration &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init");
        _keyMap.clear();
        for (int key: configuration.mappedKeys) {
            DebugLog("Adding key %d to map", key);
            _keyMap[key] = KeyState();
        }

        coreSystem->onPreEvents += [this]() { CleanKeyState(); };
        coreSystem->onKeyUp += [this](auto key) { OnKeyUp(key); };
        coreSystem->onKeyDown += [this](auto key) { OnKeyDown(key); };

        return 0;
    }

    void InputSystem::Quit() {
        DebugLog("Quit");
    }

    int InputSystem::GetInitFlags() {
        return 0;
    }

    int InputSystem::GetWindowFlags() {
        return 0;
    }
    //endregion public

    //region private
    void InputSystem::CleanKeyState() {
        for (int key: _dirtyKeys) {
            _keyMap[key].down = false;
            _keyMap[key].up = false;

            auto it = _keyMap.find(key);
        }
        _dirtyKeys.clear();
    }

    void InputSystem::OnKeyUp(SDL_KeyboardEvent &key) {
        auto it = _keyMap.find(key.keysym.sym);
        if (it == _keyMap.end()) {
            return; // key not mapped
        }

        it->second.isDown = false;
        it->second.up = true;
        _dirtyKeys.push_back(key.keysym.sym);
    }

    void InputSystem::OnKeyDown(SDL_KeyboardEvent &key) {
        auto it = _keyMap.find(key.keysym.sym);
        if (it == _keyMap.end()) {
            return; // key not mapped
        }
        if (it->second.isDown) {
            return; // key already down
        }
        it->second.down = true;
        it->second.isDown = true;
        _dirtyKeys.push_back(key.keysym.sym);
    }
    //endregion private
} // Harpia