//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUTSYSTEM_H
#define HARPIAGAMEENGINE_INPUTSYSTEM_H

#include <map>
#include <list>

#include "KeyState.h"
#include "IApplicationSystem.h"
#include "CoreDefines.h"

union SDL_Event;

namespace Harpia {
    class InputSystem : public IApplicationSystem {
    private:
        std::map<int, KeyState> _keyMap;
        std::list<int> _dirtyKeys;

    public:
        int Initialize(InputConfiguration &configuration, CoreSystem *coreSystem);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

    private:
        void CleanKeyState();

        void OnKeyDown(SDL_Event *e);

        void OnKeyUp(SDL_Event *e);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_INPUTSYSTEM_H
