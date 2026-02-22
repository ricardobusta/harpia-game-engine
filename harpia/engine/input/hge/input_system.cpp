//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "input_system.h"

#include "hge/configuration.h"
#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>

namespace {
    Harpia::KeyCode ToKeyCode(SDL_Keycode sdl) {
        using K = Harpia::KeyCode;
        switch (sdl) {
            case SDLK_A: return K::A; case SDLK_B: return K::B; case SDLK_C: return K::C;
            case SDLK_D: return K::D; case SDLK_E: return K::E; case SDLK_F: return K::F;
            case SDLK_G: return K::G; case SDLK_H: return K::H; case SDLK_I: return K::I;
            case SDLK_J: return K::J; case SDLK_K: return K::K; case SDLK_L: return K::L;
            case SDLK_M: return K::M; case SDLK_N: return K::N; case SDLK_O: return K::O;
            case SDLK_P: return K::P; case SDLK_Q: return K::Q; case SDLK_R: return K::R;
            case SDLK_S: return K::S; case SDLK_T: return K::T; case SDLK_U: return K::U;
            case SDLK_V: return K::V; case SDLK_W: return K::W; case SDLK_X: return K::X;
            case SDLK_Y: return K::Y; case SDLK_Z: return K::Z;

            case SDLK_0: return K::Alpha0; case SDLK_1: return K::Alpha1;
            case SDLK_2: return K::Alpha2; case SDLK_3: return K::Alpha3;
            case SDLK_4: return K::Alpha4; case SDLK_5: return K::Alpha5;
            case SDLK_6: return K::Alpha6; case SDLK_7: return K::Alpha7;
            case SDLK_8: return K::Alpha8; case SDLK_9: return K::Alpha9;

            case SDLK_F1:  return K::F1;  case SDLK_F2:  return K::F2;
            case SDLK_F3:  return K::F3;  case SDLK_F4:  return K::F4;
            case SDLK_F5:  return K::F5;  case SDLK_F6:  return K::F6;
            case SDLK_F7:  return K::F7;  case SDLK_F8:  return K::F8;
            case SDLK_F9:  return K::F9;  case SDLK_F10: return K::F10;
            case SDLK_F11: return K::F11; case SDLK_F12: return K::F12;

            case SDLK_UP:    return K::Up;    case SDLK_DOWN:  return K::Down;
            case SDLK_LEFT:  return K::Left;  case SDLK_RIGHT: return K::Right;

            case SDLK_SPACE:     return K::Space;
            case SDLK_RETURN:    return K::Return;
            case SDLK_ESCAPE:    return K::Escape;
            case SDLK_TAB:       return K::Tab;
            case SDLK_BACKSPACE: return K::Backspace;
            case SDLK_DELETE:    return K::Delete;
            case SDLK_INSERT:    return K::Insert;
            case SDLK_HOME:      return K::Home;
            case SDLK_END:       return K::End;
            case SDLK_PAGEUP:    return K::PageUp;
            case SDLK_PAGEDOWN:  return K::PageDown;

            case SDLK_LSHIFT: return K::LeftShift;  case SDLK_RSHIFT: return K::RightShift;
            case SDLK_LCTRL:  return K::LeftCtrl;   case SDLK_RCTRL:  return K::RightCtrl;
            case SDLK_LALT:   return K::LeftAlt;    case SDLK_RALT:   return K::RightAlt;
            case SDLK_LGUI:   return K::LeftSuper;  case SDLK_RGUI:   return K::RightSuper;
            case SDLK_CAPSLOCK:   return K::CapsLock;
            case SDLK_NUMLOCKCLEAR: return K::NumLock;
            case SDLK_SCROLLLOCK:   return K::ScrollLock;

            case SDLK_KP_0: return K::Numpad0; case SDLK_KP_1: return K::Numpad1;
            case SDLK_KP_2: return K::Numpad2; case SDLK_KP_3: return K::Numpad3;
            case SDLK_KP_4: return K::Numpad4; case SDLK_KP_5: return K::Numpad5;
            case SDLK_KP_6: return K::Numpad6; case SDLK_KP_7: return K::Numpad7;
            case SDLK_KP_8: return K::Numpad8; case SDLK_KP_9: return K::Numpad9;
            case SDLK_KP_ENTER:    return K::NumpadEnter;
            case SDLK_KP_PLUS:     return K::NumpadPlus;
            case SDLK_KP_MINUS:    return K::NumpadMinus;
            case SDLK_KP_MULTIPLY: return K::NumpadMultiply;
            case SDLK_KP_DIVIDE:   return K::NumpadDivide;
            case SDLK_KP_PERIOD:   return K::NumpadPeriod;

            case SDLK_MINUS:        return K::Minus;
            case SDLK_EQUALS:       return K::Equals;
            case SDLK_LEFTBRACKET:  return K::LeftBracket;
            case SDLK_RIGHTBRACKET: return K::RightBracket;
            case SDLK_BACKSLASH:    return K::Backslash;
            case SDLK_SEMICOLON:    return K::Semicolon;
            case SDLK_APOSTROPHE:   return K::Apostrophe;
            case SDLK_GRAVE:        return K::Grave;
            case SDLK_COMMA:        return K::Comma;
            case SDLK_PERIOD:       return K::Period;
            case SDLK_SLASH:        return K::Slash;

            case SDLK_PRINTSCREEN: return K::PrintScreen;
            case SDLK_PAUSE:       return K::Pause;

            default: return K::Unknown;
        }
    }
}

namespace Harpia::Internal {
    //region public
    int InputSystem::Initialize(InputConfiguration &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init Input");

        _keyMap.clear();
        for (Harpia::KeyCode key: configuration.mappedKeys) {
            _keyMap[key] = KeyState();
        }

        _inputReader = new InputReader(&_mouseState, &_keyMap, [this](auto key) {
            DebugLogWarning("Unmapped key encountered, consider adding it in the game configs");
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
        for (Harpia::KeyCode key: _dirtyKeys) {
            CleanKeyState(_keyMap[key]);
        }
        _dirtyKeys.clear();

        for (auto i = 0; i < MouseState::MOUSE_BUTTON_COUNT; i++) {
            CleanKeyState(_mouseState.mouseButton[i]);
        }
    }

    void InputSystem::OnKeyUp(const SDL_KeyboardEvent &key) {
        auto keyCode = ToKeyCode(key.key);
        auto it = _keyMap.find(keyCode);
        if (it == _keyMap.end()) {
            return;// key not mapped
        }

        it->second.isDown = false;
        it->second.up = true;
        _dirtyKeys.push_back(keyCode);
    }

    void InputSystem::OnKeyDown(const SDL_KeyboardEvent &key) {
        auto keyCode = ToKeyCode(key.key);
        auto it = _keyMap.find(keyCode);
        if (it == _keyMap.end()) {
            return;// key not mapped
        }
        if (it->second.isDown) {
            return;// key already down
        }
        it->second.down = true;
        it->second.isDown = true;
        _dirtyKeys.push_back(keyCode);
    }

    void InputSystem::OnMouseWheel(SDL_MouseWheelEvent &wheel) {
        _mouseState.wheelDelta.x = (int) wheel.x;
        _mouseState.wheelDelta.y = (int) wheel.y;
    }

    void InputSystem::OnMouseMove(SDL_MouseMotionEvent &motion) {
        _mouseState.pos.x = (int) motion.x;
        _mouseState.pos.y = (int) motion.y;
    }

    void InputSystem::OnMouseUp(SDL_MouseButtonEvent &button) {
        // SDL button indices are 1-based; MouseButton enum is 0-based with matching order
        auto index = static_cast<int>(button.button) - 1;
        if (index < 0 || index >= MouseState::MOUSE_BUTTON_COUNT) return;
        auto &b = _mouseState.mouseButton[index];
        b.isDown = false;
        b.up = true;
    }

    void InputSystem::OnMouseDown(SDL_MouseButtonEvent &button) {
        auto index = static_cast<int>(button.button) - 1;
        if (index < 0 || index >= MouseState::MOUSE_BUTTON_COUNT) return;
        auto &b = _mouseState.mouseButton[index];
        b.isDown = true;
        b.down = true;
    }
    void InputSystem::CleanKeyState(KeyState &key) {
        key.down = false;
        key.up = false;
    }
    //endregion private
}// namespace Harpia::Internal