//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Application.h"

#include <SDL.h>

#include "Debug.h"
#include "Configuration.h"
#include "Renderer.h"
#include "Input.h"

namespace Harpia {
    Application::Application(Renderer * renderer) {
        DebugLog("Application created");
        configuration = new Configuration();
    };

    Application::~Application() {
        DebugLog("Application destroyed");
        delete configuration;
    }

    int Application::Execute() {
        DebugLog("Application %s is starting", configuration->gameTitle.c_str());
        _result = Initialize();
        if (_result != 0) {
            return _result;
        }

        _keyMap.clear();
        for (int key: *configuration->mappedKeys) {
            DebugLog("Adding key %d to map", key);
            _keyMap[key] = KeyState();
        }

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            CleanKeyState();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        DebugLog("Requested to quit");
                        break;
                    case SDL_KEYDOWN: {
                        auto it = _keyMap.find(e.key.keysym.sym);
                        if (it != _keyMap.end()) {
                            if (!it->second.isDown) {
                                it->second.down = true;
                                it->second.isDown = true;
                                _dirtyKeys.push_back(e.key.keysym.sym);
                            }

                            auto k = &it->second;
                            DebugLog("KeyState isDown: %d down: %d up: %d", k->isDown, k->down, k->up);
                        }
                        break;
                    }
                    case SDL_KEYUP: {
                        auto it = _keyMap.find(e.key.keysym.sym);
                        if (it != _keyMap.end()) {
                            it->second.isDown = false;
                            it->second.up = true;
                            _dirtyKeys.push_back(e.key.keysym.sym);

                            auto k = &it->second;
                            DebugLog("KeyState isDown: %d down: %d up: %d", k->isDown, k->down, k->up);
                        }
                        break;
                    }
                }
            }

            FrameUpdate();
        }

        DebugLog("Quit");
        Quit();
        return _result;
    }

    int Application::Initialize() {
        auto result = SDL_Init(SDL_INIT_VIDEO);
        if (result < 0) {
            DebugLogError("SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(configuration->gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration->windowSize.x, configuration->windowSize.y,
                                   SDL_WINDOW_SHOWN);

        if (result < 0) {
            DebugLogError("Failed to start Renderer. SDL_Error: %s\n", SDL_GetError());
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

    void Application::CleanKeyState() {
        for (int key: _dirtyKeys) {
            _keyMap[key].down = false;
            _keyMap[key].up = false;

            auto it = _keyMap.find(key);
            auto k = &it->second;
            DebugLog("Cleaning. KeyState isDown: %d down: %d up: %d", k->isDown, k->down, k->up);
        }
        _dirtyKeys.clear();
    }
}