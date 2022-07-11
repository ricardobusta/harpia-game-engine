//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "core_system.h"

#include "hge/configuration.h"
#include "hge/debug.h"
#include <SDL.h>

namespace Harpia::Internal {
    int CoreSystem::Initialize(Configuration &config, int InitFlags, int WindowFlags) {
        auto result = SDL_Init(InitFlags);
        if (result < 0) {
            DebugLogError("SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(config.game.title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, config.window.size.x, config.window.size.y, WindowFlags);
        if (_window == nullptr) {
            DebugLogError("Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        _time.now = SDL_GetTicks64();

        return 0;
    }

    int CoreSystem::Execute() {
        onInitialize.Invoke();

        bool quit = false;
        SDL_Event e;

        while (true) {
            auto now = _time.timeScale * (float) SDL_GetTicks64() / 1000.0f;
            _time.deltaTime = now - _time.now;
            _time.now = now;
            onPreEvents.Invoke();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        onQuit.Invoke();
                        quit = true;
                        DebugLog("Requested to quit");
                        break;
                    case SDL_KEYDOWN: {
                        onKeyDown.Invoke(e.key);
                        break;
                    }
                    case SDL_KEYUP: {
                        onKeyUp.Invoke(e.key);
                        break;
                    }
                }
            }

            if (quit) {
                break;
            }

            onUpdate.Invoke();
            onRenderStep.Invoke();
            onLateUpdate.Invoke();
        }
        return 0;
    }

    int CoreSystem::GetInitFlags() {
        return SDL_INIT_VIDEO;
    }

    int CoreSystem::GetWindowFlags() {
        return SDL_WINDOW_SHOWN;
    }

    void CoreSystem::Quit() {
        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }

    SDL_Window *CoreSystem::GetWindow() {
        return _window;
    }

    const Time *CoreSystem::GetTime() const {
        return &_time;
    }
}// namespace Harpia::Internal