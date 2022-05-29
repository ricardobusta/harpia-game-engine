//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <SDL.h>

#include "Application.h"

namespace Harpia::Engine {
    Application::Application(Configuration configuration) {

    }

    bool Application::Execute() {
        _result = Initialize();
        if(_result!=0){
            return false;
        }

        bool quit = false;
        SDL_Event e;

        while(!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if(e.type == SDL_QUIT){
                    quit = true;
                }
            }

            SDL_FillRect(_surface, nullptr, SDL_MapRGB(_surface->format, 0, 0, 0));
            SDL_UpdateWindowSurface(_window);
        }
        Quit();
        return true;
    }

    int Application::Result() {
        return _result;
    }

    int Application::Initialize() {
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

    void Application::Quit() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }
}