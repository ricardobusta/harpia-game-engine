//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Application.h"

#include <SDL.h>

#include "Debug.h"
#include "Renderer.h"
#include "Input.h"

namespace Harpia {
    Application::Application(Renderer *renderer) {
        if (renderer == nullptr) {
            DebugLogError("[Application] No renderer set.");
            return;
        }
        _renderer = renderer;

        _input = new Input();

        _createdWithSuccess = true;
        DebugLog("[Application] Application created");
    }

    Application::~Application() {
        delete _input;
        DebugLog("[Application] Application destroyed");
    }

    int Application::Initialize() {
        auto result = SDL_Init(SDL_INIT_VIDEO);
        if (result < 0) {
            DebugLogError("[Application] SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(configuration.gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration.windowSize.x, configuration.windowSize.y,
                                   SDL_WINDOW_SHOWN | _renderer->GetWindowFlags());

        if (_window == nullptr) {
            DebugLogError("[Application] Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        result = _renderer->Initialize(&configuration, _window);

        if (result < 0) {
            DebugLogError("[Application] Renderer was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        result = _input->Initialize(&configuration);
        if (result < 0) {
            DebugLogError("[Application] Input was not initialized. SDL_Error: %s", SDL_GetError());
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
            DebugLogError("[Application] Application not created with success.");
            return -1;
        }

        DebugLog("[Application] Application %s is starting", configuration.gameTitle.c_str());
        _result = Initialize();
        if (_result != 0) {
            return _result;
        }

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            _input->CleanKeyState();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        DebugLog("Requested to quit");
                        break;
                    case SDL_KEYDOWN: {
                        _input->OnKeyDown(&e);
                        break;
                    }
                    case SDL_KEYUP: {
                        _input->OnKeyUp(&e);
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
}