//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Application.h"

#include "Debug.h"
#include "AudioSystem.h"
#include "CoreSystem.h"
#include "InputSystem.h"
#include "RenderingSystemGL.h"
#include "SceneSystem.h"

#define SystemInit(system, args...) do{auto result = system->Initialize(args); \
if (result < 0) {DebugLogError("%s was not initialized.", #system);return result;}}while(0);

#define SystemCleanup(system) do{delete system;system=nullptr;}while(0);

namespace Harpia {
    Application::Application(const std::function<void(Configuration &)> &configure) {
        if (configure == nullptr) {
            DebugLogError("Configure method missing");
            return;
        }

        configure(configuration);

        _coreSystem = new Internal::CoreSystem();
        _renderSystem = new Internal::RenderingSystemGL();
        _inputSystem = new Internal::InputSystem();
        _audioSystem = new Internal::AudioSystem();
        _sceneManagementSystem = new Internal::SceneSystem();

        _createdWithSuccess = true;
    }

    Application::~Application() = default;

    int Application::Execute() {
        if (!_createdWithSuccess) {
            DebugLogError("Application not created with success.");
            return -1;
        }

        DebugLog("Application %s is starting", configuration.game.title.c_str());

        SystemInit(_coreSystem, configuration, GetInitFlags(), GetWindowFlags());
        SystemInit(_renderSystem, configuration.game, _coreSystem);
        SystemInit(_inputSystem, configuration.input, _coreSystem);
        SystemInit(_audioSystem, configuration.audio, _coreSystem);
        SystemInit(_sceneManagementSystem, configuration.game, this, _coreSystem);

        DebugLog("All systems initialized");

        auto result = _coreSystem->Execute();
        if (result < 0) {
            DebugLogError("Application executed with an error");
        }

        _audioSystem->Quit();
        _inputSystem->Quit();
        _renderSystem->Quit();
        _coreSystem->Quit();

        DebugLog("All systems quit");

        SystemCleanup(_audioSystem);
        SystemCleanup(_inputSystem);
        SystemCleanup(_renderSystem);
        SystemCleanup(_coreSystem);

        DebugLog("Quit");
        return result;
    }

    int Application::GetWindowFlags() {
        return _coreSystem->GetWindowFlags() |
               _renderSystem->GetWindowFlags();
    }

    int Application::GetInitFlags() {
        return _coreSystem->GetInitFlags() |
               _audioSystem->GetInitFlags();
    }
}

#undef SystemInit
#undef SystemCleanup