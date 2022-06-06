//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUTSYSTEM_H
#define HARPIAGAMEENGINE_INPUTSYSTEM_H

#include <map>
#include <list>

#include "KeyState.h"
#include "IApplicationSystem.h"
#include "GlobalDefines.h"
#include "InputReader.h"

namespace Harpia {
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

#endif //HARPIAGAMEENGINE_INPUTSYSTEM_H
