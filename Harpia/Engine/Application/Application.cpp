//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Application.h"

#include <SDL.h>

#include "Debug.h"
#include "RenderingSystemGL.h"
#include "InputSystem.h"
#include "AudioSystem.h"

namespace Harpia {
    Application::Application(void(*configure)(Configuration &config)) {
        if (configure == nullptr) {
            DebugLogError("Configure method missing");
            return;
        }

        _renderSystem = new RenderingSystemGL();
        _inputSystem = new InputSystem();
        _audioSystem = new AudioSystem();

        _createdWithSuccess = true;

        configure(configuration);
    }

    Application::~Application() {
        delete _renderSystem;
        _renderSystem = nullptr;

        delete _audioSystem;
        _audioSystem = nullptr;

        delete _inputSystem;
        _inputSystem = nullptr;

        DebugLog("Application destroyed");
    }

    int Application::Initialize() {
        auto result = SDL_Init(SDL_INIT_VIDEO | _audioSystem->GetInitFlags());
        if (result < 0) {
            DebugLogError("SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        _window = SDL_CreateWindow(configuration.game.title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, configuration.window.size.x, configuration.window.size.y,
                                   SDL_WINDOW_SHOWN | _renderSystem->GetWindowFlags());

        if (_window == nullptr) {
            DebugLogError("Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        result = _renderSystem->Initialize(configuration.game, _window);
        if (result < 0) {
            DebugLogError("RenderSystem was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        result = _inputSystem->Initialize(configuration.input);
        if (result < 0) {
            DebugLogError("InputSystem was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        result = _audioSystem->Initialize(configuration.audio);
        if (result < 0) {
            DebugLogError("AudioSystem was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        return 0;
    }

    void Application::Quit() {
        _renderSystem->Quit();
        _audioSystem->Quit();
        _inputSystem->Quit();

        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
        DebugLog("Quit");
    }

    int Application::Execute() {
        if (!_createdWithSuccess) {
            DebugLogError("Application not created with success.");
            return -1;
        }

        DebugLog("Application %s is starting", configuration.game.title.c_str());
        _result = Initialize();
        if (_result != 0) {
            return _result;
        }

        // TODO ===== Remove test code
        auto testAudio = _audioSystem->LoadAudio("test.wav");

        // TODO ===== Remove test code END

        bool quit = false;
        SDL_Event e;

        while (!quit) {
            _inputSystem->CleanKeyState();

            while (SDL_PollEvent(&e) != 0) {
                switch (e.type) {
                    case SDL_QUIT:
                        quit = true;
                        DebugLog("Requested to quit");
                        break;
                    case SDL_KEYDOWN: {
                        _inputSystem->OnKeyDown(&e);
                        break;
                    }
                    case SDL_KEYUP: {
                        _inputSystem->OnKeyUp(&e);
                        if (e.key.keysym.sym == SDLK_UP) {
                            _audioSystem->PlayAudio(testAudio);
                        }
                        break;
                    }
                }
            }

            _renderSystem->UpdateFrame();
        }

        Quit();
        return _result;
    }
}