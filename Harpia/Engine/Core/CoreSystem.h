//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_CORESYSTEM_H
#define HARPIAGAMEENGINE_CORESYSTEM_H

#include <list>
#include "GlobalDefines.h"
#include "IApplicationSystem.h"
#include "Event.h"

namespace Harpia {
    class CoreSystem : public IApplicationSystem {
    public:
        Event<> onInitialize;
        Event<> onUpdate;
        Event<> onRendering;
        Event<> onLateUpdate;
        Event<> onQuit;
        Event<> onPreEvents;
        Event<SDL_KeyboardEvent &> onKeyDown;
        Event<SDL_KeyboardEvent &> onKeyUp;
    private:
        SDL_Window *_window = nullptr;
        Configuration *_configuration;
    public:
        int Initialize(Configuration &config, int InitFlags, int WindowFlags);

        int Execute();

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

        SDL_Window *GetWindow();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_CORESYSTEM_H
