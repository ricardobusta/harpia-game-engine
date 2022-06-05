//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_CORESYSTEM_H
#define HARPIAGAMEENGINE_CORESYSTEM_H

#include <list>
#include "CoreDefines.h"
#include "IApplicationSystem.h"
#include "Event.h"

namespace Harpia {
    class CoreSystem : public IApplicationSystem {
    public:
        Event<> onUpdate;
        Event<> onQuit;
        Event<> onPreEvents;
        Event<SDL_Event &> onKeyDown;
        Event<SDL_Event &> onKeyUp;
    public:
        int Initialize(Configuration &config, int InitFlags, int WindowFlags);

        int Execute();

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

        SDL_Window *GetWindow();

    private:
        SDL_Window *_window = nullptr;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_CORESYSTEM_H
