//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <SDL.h>

#include "Application.h"
#include "Debug.h"
#include "OpenGLApplication.h"
#include "Configuration.h"

namespace Harpia::Engine {
    Application::Application() {
        Debug::Log("Application created");
        configuration = new Configuration();
    };

    Application::~Application() {
        Debug::Log("Application destroyed");
        delete (configuration);
    }

    int Application::Execute() {
        Debug::Log("Application %s is starting", configuration->gameTitle.c_str());
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

            FrameUpdate();
        }

        Debug::Log("Quit");
        Quit();
        return _result;
    }

    int Application::Initialize() {
        auto result = SDL_Init(SDL_INIT_VIDEO);
        if (result < 0) {
            Debug::LogError("SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(configuration->gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration->windowSize.x, configuration->windowSize.y,
                                   SDL_WINDOW_SHOWN);

        if (result < 0) {
            Debug::LogError("Failed to start Renderer. SDL_Error: %s\n", SDL_GetError());
            return result;
        }

        _surface = SDL_GetWindowSurface(_window);

        return 0;
    }

    void Application::FrameUpdate() {
        auto color = configuration->clearColor;
        SDL_FillRect(_surface, nullptr, SDL_MapRGB(_surface->format, color.r, color.g, color.b));
        SDL_UpdateWindowSurface(_window);
    }

    void Application::Quit() {
        SDL_FreeSurface(_surface);
        _surface = nullptr;

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }
}