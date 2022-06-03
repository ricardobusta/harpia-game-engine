//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "Renderer.h"

#include <SDL.h>

#include "Debug.h"
#include "Configuration.h"

namespace Harpia {
    int Renderer::GetWindowFlags() {
        return 0;
    }

    int Renderer::Initialize(Configuration *configuration, SDL_Window *window) {
        if (configuration == nullptr) {
            DebugLogError("Configuration is null.");
            return -1;
        }

        _configuration = configuration;

        if(window == nullptr){
            DebugLogError("Window is null.");
            return -1;
        }

        _window = window;

        _surface = SDL_GetWindowSurface(window);
        if (_surface == nullptr) {
            DebugLogError("SDL Surface not created. SDL_Error: %s", SDL_GetError());
            return -1;
        }
        return 0;
    }

    void Renderer::UpdateFrame() {
        auto color = _configuration->clearColor;
        SDL_FillRect(_surface, nullptr, SDL_MapRGB(_surface->format, color.r, color.g, color.b));
        SDL_UpdateWindowSurface(_window);
    }

    void Renderer::Destroy() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;
    }
} // Harpia