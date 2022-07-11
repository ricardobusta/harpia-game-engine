//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_CORESYSTEM_H
#define HARPIAGAMEENGINE_CORESYSTEM_H

#include "event.h"
#include "global_defines.h"
#include "hge/time.h"
#include "i_application_system.h"
#include <list>

namespace Harpia::Internal {
    class CoreSystem : public IApplicationSystem {
    public:
        Event<> onInitialize;
        Event<> onUpdate;
        Event<> onRenderStep;
        Event<> onLateUpdate;
        Event<> onQuit;
        Event<> onPreEvents;
        Event<SDL_KeyboardEvent &> onKeyDown;
        Event<SDL_KeyboardEvent &> onKeyUp;

    private:
        SDL_Window *_window = nullptr;
        Time _time;

    public:
        int Initialize(Configuration &config, int InitFlags, int WindowFlags);

        int Execute();

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

        [[nodiscard]] const Time * GetTime() const;

        SDL_Window *GetWindow();
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_CORESYSTEM_H
