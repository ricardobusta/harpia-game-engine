//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "input_system.h"

#include "hge/configuration.h"
#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"
#include <SDL_events.h>

namespace Harpia::Internal {
    //region public
    int InputSystem::Initialize(InputConfiguration &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init Input");

        _keyMap.clear();
        for (int key: configuration.mappedKeys) {
            DebugLog("Adding key %d to map", key);
            _keyMap[key] = KeyState();
        }

        _inputReader = new InputReader(&_mouseState, &_keyMap, [this](auto key) {
            DebugLogWarning("Key %d not mapped, consider adding it in the game configs", key);
            _keyMap[key] = KeyState();
        });

        coreSystem->onPreEvents += [this]() { CleanKeyState(); };

        coreSystem->onKeyUp += [this](auto key) { OnKeyUp(key); };
        coreSystem->onKeyDown += [this](auto key) { OnKeyDown(key); };

        coreSystem->onMouseWheel += [this](auto e) { OnMouseWheel(e); };
        coreSystem->onMouseButtonUp += [this](auto e) { OnMouseUp(e); };
        coreSystem->onMouseButtonDown += [this](auto e) { OnMouseDown(e); };
        coreSystem->onMouseMove += [this](auto e) { OnMouseMove(e); };

        return 0;
    }

    void InputSystem::Quit() {
        delete _inputReader;
        _inputReader = nullptr;
        DebugLog("Quit Input");
    }

    int InputSystem::GetInitFlags() {
        return 0;
    }

    int InputSystem::GetWindowFlags() {
        return 0;
    }

    InputReader *InputSystem::GetInputReader() {
        return _inputReader;
    }
    //endregion public

    //region private
    void InputSystem::CleanKeyState() {
        for (int key: _dirtyKeys) {
            CleanKeyState(_keyMap[key]);
        }
        _dirtyKeys.clear();

        for (auto i = 0; i < MouseState::MOUSE_BUTTON_COUNT; i++) {
            CleanKeyState(_mouseState.mouseButton[i]);
        }
    }

    void InputSystem::OnKeyUp(const SDL_KeyboardEvent &key) {
        auto it = _keyMap.find(key.keysym.sym);
        if (it == _keyMap.end()) {
            return;// key not mapped
        }

        it->second.isDown = false;
        it->second.up = true;
        _dirtyKeys.push_back(key.keysym.sym);
    }

    void InputSystem::OnKeyDown(const SDL_KeyboardEvent &key) {
        auto it = _keyMap.find(key.keysym.sym);
        if (it == _keyMap.end()) {
            return;// key not mapped
        }
        if (it->second.isDown) {
            return;// key already down
        }
        it->second.down = true;
        it->second.isDown = true;
        _dirtyKeys.push_back(key.keysym.sym);
    }

    void InputSystem::OnMouseWheel(SDL_MouseWheelEvent &wheel) {
        _mouseState.wheelDelta.x = wheel.x;
        _mouseState.wheelDelta.y = wheel.y;
    }

    void InputSystem::OnMouseMove(SDL_MouseMotionEvent &motion) {
        _mouseState.pos.x = motion.x;
        _mouseState.pos.y = motion.y;
    }

    void InputSystem::OnMouseUp(SDL_MouseButtonEvent &button) {
        auto &b = _mouseState.mouseButton[button.button - 1];
        b.isDown = false;
        b.up = true;
    }

    void InputSystem::OnMouseDown(SDL_MouseButtonEvent &button) {
        auto &b = _mouseState.mouseButton[button.button - 1];
        b.isDown = true;
        b.down = true;
    }
    void InputSystem::CleanKeyState(KeyState &key) {
        key.down = false;
        key.up = false;
    }
    //endregion private
}// namespace Harpia::Internal