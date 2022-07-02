//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "hge/rendering_system_sdl.h"

#include "hge/color.h"
#include "hge/debug.h"
#include <SDL.h>

namespace Harpia::Internal {
    void RenderingSystemSDL::RenderFrame() {
        auto clearColor = SDL_MapRGBA(_surface->format, _clearColor->IntR(), _clearColor->IntG(), _clearColor->IntB(),
                                      _clearColor->IntA());
        SDL_FillRect(_surface, nullptr, clearColor);
        SDL_UpdateWindowSurface(_window);
    }

    int RenderingSystemSDL::GetWindowFlags() {
        return 0;
    }

    void RenderingSystemSDL::Quit() {
        RenderingSystem::Quit();

        SDL_FreeSurface(_surface);
        _surface = nullptr;
        delete _clearColor;
        _clearColor = nullptr;
        DebugLog("Quit");
    }

    int RenderingSystemSDL::RenderingInitialize() {
        _clearColor = new Color(0, 0, 0, 1);
        _surface = SDL_GetWindowSurface(_window);
        if (_surface == nullptr) {
            DebugLogError("SDL Surface not created. SDL_Error: %s", SDL_GetError());
            return -1;
        }

        return 0;
    }
}// namespace Harpia::Internal