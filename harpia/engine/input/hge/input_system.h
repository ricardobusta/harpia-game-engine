//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_SYSTEM_H
#define HARPIAGAMEENGINE_INPUT_SYSTEM_H

#include <list>
#include <map>

#include "hge/i_application_system.h"
#include "hge/input_reader.h"
#include "hge/internal_defines.h"
#include "hge/key_state.h"
#include "hge/mouse_state.h"

namespace Harpia::Internal {
    class InputSystem : public IApplicationSystem {
    private:
        std::map<SDL_Keycode, KeyState> _keyMap;
        std::list<SDL_Keycode> _dirtyKeys;
        MouseState _mouseState;
        InputReader *_inputReader;

    public:
        int Initialize(InputConfiguration &configuration, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;
        InputReader *GetInputReader();

    private:
        void CleanKeyState();
        void CleanKeyState(KeyState&key);

        void OnKeyDown(const SDL_KeyboardEvent &key);
        void OnKeyUp(const SDL_KeyboardEvent &key);

        void OnMouseWheel(SDL_MouseWheelEvent &wheel);
        void OnMouseMove(SDL_MouseMotionEvent &motion);
        void OnMouseUp(SDL_MouseButtonEvent &button);
        void OnMouseDown(SDL_MouseButtonEvent &button);
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_INPUT_SYSTEM_H
