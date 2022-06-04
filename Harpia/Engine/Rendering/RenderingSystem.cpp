//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "RenderingSystem.h"

#include <SDL.h>

#include "Debug.h"
#include "Configuration.h"

namespace Harpia {
    int RenderingSystem::Initialize(GameConfiguration &configuration, SDL_Window *window) {
        DebugLog("Init");
        _clearColor = &configuration.clearColor;

        if (window == nullptr) {
            DebugLogError("Window is null.");
            return -1;
        }
        _window = window;

        auto result = RenderingInitialize();
        if (result < 0) {
            DebugLogError("Failed to initialize specifics.");
            return result;
        }

        return 0;
    }

    void RenderingSystem::UpdateFrame() {
        auto clearColor = SDL_MapRGBA(_surface->format, _clearColor->IntR(), _clearColor->IntG(), _clearColor->IntB(), _clearColor->IntA());
        SDL_FillRect(_surface, nullptr,clearColor);
        SDL_UpdateWindowSurface(_window);
    }

    int RenderingSystem::GetInitFlags() {
        return 0;
    }

    int RenderingSystem::GetWindowFlags() {
        return 0;
    }

    void RenderingSystem::Quit() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;
        DebugLog("Quit");
    }

    int RenderingSystem::RenderingInitialize() {
        _surface = SDL_GetWindowSurface(_window);
        if (_surface == nullptr) {
            DebugLogError("SDL Surface not created. SDL_Error: %s", SDL_GetError());
            return -1;
        }

        return 0;
    }
} // Harpia