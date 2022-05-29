//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <SDL.h>
#include <iostream>

#include "Application.h"

#include "Debug.h"

namespace Harpia::Engine {
    Application::Application() = default;

    int Application::Execute() {
        Debug::Log("Application is starting");
        _result = Initialize();
        if (_result != 0) {
            return _result;
        }

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                    Debug::Log("Requested to quit");
                }
            }

            SDL_FillRect(_surface, nullptr,
                         SDL_MapRGB(_surface->format, configuration.clearColor.r, configuration.clearColor.g,
                                    configuration.clearColor.b));
            SDL_UpdateWindowSurface(_window);
        }
        Debug::Log("Quit");
        Quit();
        return _result;
    }

    int Application::Initialize() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        _window = SDL_CreateWindow(configuration.gameTitle.ToCString(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration.windowSize.x, configuration.windowSize.y,
                                   SDL_WINDOW_SHOWN);

        if (_window == nullptr) {
            fprintf(stderr, "Window was not created. SDL_Error: %s\n", SDL_GetError());
            return 1;
        }

        _surface = SDL_GetWindowSurface(_window);

        return 0;
    }

    void Application::Quit() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }
}