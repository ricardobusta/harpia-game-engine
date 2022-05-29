//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Core.h"
#include "SDL.h"
#include <iostream>

namespace Harpia::Engine {
    int Core::Start() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        _window = SDL_CreateWindow("Test SDL", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, 640, 480,
                                   SDL_WINDOW_SHOWN);

        if (_window == nullptr) {
            fprintf(stderr, "Window was not created. SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        _surface = SDL_GetWindowSurface(_window);

        return 0;
    }

    void Core::Draw() {
        SDL_FillRect(_surface, nullptr, SDL_MapRGB(_surface->format, 0, 0, 0));
        SDL_UpdateWindowSurface(_window);
        SDL_Delay(15000);
        SDL_DestroyWindow(_window);
    }

    void Core::Quit() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }
}// namespace Harpia::Engine