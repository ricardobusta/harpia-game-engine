//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "application.h"

#include "hge/audio_system.h"
#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/input_system.h"
#include "hge/system_gl/rendering_system_gl.h"
#include "hge/scene_system.h"

#define SystemInit(system, args...)                            \
    do {                                                       \
        _systems.push_front(system);                           \
        auto result = system->Initialize(args);                \
        if (result < 0) {                                      \
            DebugLogError("%s was not initialized.", #system); \
            return result;                                     \
        }                                                      \
    } while (0);

#define SystemCleanup(system) \
    do {                      \
        delete system;        \
        system = nullptr;     \
    } while (0);

namespace Harpia {
    Application::Application(const std::function<void(Configuration &)> &configure) {
        if (configure == nullptr) {
            DebugLogError("Configure method missing");
            return;
        }

        configure(configuration);
        screenSize = configuration.window.size;

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

        for (auto it = _systems.begin(); it != _systems.end(); it++) {
            (*it)->Quit();
        }

        DebugLog("All systems quit");

        SystemCleanup(_sceneManagementSystem);
        SystemCleanup(_audioSystem);
        SystemCleanup(_inputSystem);
        SystemCleanup(_renderSystem);
        SystemCleanup(_coreSystem);

        DebugLog("Quit Application");
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
}// namespace Harpia

#undef SystemInit
#undef SystemCleanup