//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>
#include "Core.h"

#include "SDL.h"

namespace Harpia {
    int Core::HelloWorld(Configuration configuration) {
        SDL_Window *window = nullptr;
        SDL_Surface *screenSurface = nullptr;
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
            return 1;
        }
        window = SDL_CreateWindow(
                "hello_sdl2",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                configuration.windowSize.x, configuration.windowSize.y,
                SDL_WINDOW_SHOWN
        );
        if (window == nullptr) {
            fprintf(stderr, "could not create window: %s\n", SDL_GetError());
            return 1;
        }
        screenSurface = SDL_GetWindowSurface(window);
        SDL_FillRect(screenSurface, nullptr,
                     SDL_MapRGB(screenSurface->format, configuration.clearColor.r, configuration.clearColor.g,
                                configuration.clearColor.b));
        SDL_UpdateWindowSurface(window);
        SDL_Delay(2000);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 0;
    }
}