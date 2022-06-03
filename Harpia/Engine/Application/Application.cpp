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
    Application::Application(Renderer *renderer) {
        configuration = new Configuration();

        if (renderer == nullptr) {
            DebugLogError("No renderer set.");
            return;
        }
        _renderer = renderer;

        _createdWithSuccess = true;
        DebugLog("Application created");
    };

    Application::~Application() {
        delete configuration;
        DebugLog("Application destroyed");
    }

    int Application::Initialize() {
        auto result = SDL_Init(SDL_INIT_VIDEO);
        if (result < 0) {
            DebugLogError("SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(configuration->gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration->windowSize.x, configuration->windowSize.y,
                                   SDL_WINDOW_SHOWN);

        if (_window == nullptr) {
            DebugLogError("Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        result = _renderer->Initialize(configuration, _window);

        if (result < 0) {
            DebugLogError("Renderer was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        return 0;
    }

    void Application::Quit() {
        _renderer->Destroy();
        delete _renderer;
        _renderer = nullptr;

        delete _input;
        _input = nullptr;

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }

    int Application::Execute() {
        if (!_createdWithSuccess) {
            DebugLogError("Application not created with success.");
            return -1;
        }

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

            _renderer->UpdateFrame();
        }

        DebugLog("Quit");
        Quit();
        return _result;
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