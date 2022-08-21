//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_CORESYSTEM_H
#define HARPIAGAMEENGINE_CORESYSTEM_H

#include "event.h"
#include "hge/time.h"
#include "i_application_system.h"
#include "internal_defines.h"
#include "hge/harpia_math.h"
#include <list>

namespace Harpia::Internal {
    class CoreSystem : public IApplicationSystem {
    public:
        Event<> onInitialize;
        Event<> onSceneChanges;
        Event<> onUpdate;
        Event<> onRenderStep;
        Event<> onLateUpdate;
        Event<> onQuit;
        Event<> onPreEvents;
        Event<const SDL_KeyboardEvent &> onKeyDown;
        Event<const SDL_KeyboardEvent &> onKeyUp;
        Event<const SDL_MouseMotionEvent &> onMouseMove;
        Event<const SDL_MouseButtonEvent &> onMouseButtonDown;
        Event<const SDL_MouseButtonEvent &> onMouseButtonUp;
        Event<const SDL_MouseWheelEvent &> onMouseWheel;
        Event<Vector2> onWindowResize;

    private:
        SDL_Window *_window = nullptr;
        Time _time;
        bool _quit = false;
        Uint64 _fpsCap = 0;
        Uint64 _frameStartTick;

    public:
        int Initialize(const Configuration &config, int InitFlags, int WindowFlags);
        int Execute();
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;
        [[nodiscard]] const Time *GetTime() const;
        SDL_Window *GetWindow();

    private:
        [[nodiscard]] float CalculateNow() const;
        [[nodiscard]] Uint64 NowTick() const;
        void HandleWindowEvent(const SDL_Event &e);
        void HandleEvents(const SDL_Event &e);
        void FrameDelay() const;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_CORESYSTEM_H
