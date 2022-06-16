//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_SYSTEM_H
#define HARPIAGAMEENGINE_INPUT_SYSTEM_H

#include <map>
#include <list>

#include "hge/key_state.h"
#include "hge/i_application_system.h"
#include "hge/global_defines.h"
#include "hge/internal_defines.h"
#include "hge/input_reader.h"

namespace Harpia::Internal {
    class InputSystem : public IApplicationSystem {
    private:
        std::map<SDL_Keycode, KeyState> _keyMap;
        std::list<SDL_Keycode> _dirtyKeys;
        InputReader *_inputReader;
    public:
        int Initialize(InputConfiguration &configuration, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;
        InputReader *GetInputReader();
    private:
        void CleanKeyState();
        void OnKeyDown(SDL_KeyboardEvent &key);
        void OnKeyUp(SDL_KeyboardEvent &key);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_INPUT_SYSTEM_H