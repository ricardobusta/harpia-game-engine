//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "application.h"

#include "hge/audio_system.h"
#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/input_system.h"
#include "hge/scene_system.h"
#include "hge/system_gl/rendering_system_gl.h"

#define SystemInit(system, args...)                            \
    do {                                                       \
        _systems.push_front(system.get());                     \
        auto result = system->Initialize(args);                \
        if (result < 0) {                                      \
            DebugLogError("%s was not initialized.", #system); \
            return result;                                     \
        }                                                      \
    } while (0)

namespace Harpia {
    Application::Application(const std::function<void(Configuration &)> &configure) {
        if (configure == nullptr) {
            DebugLogError("Configure method missing");
            return;
        }

        configure(configuration);
        screenSize = configuration.window.size;

        _coreSystem = std::make_unique<Internal::CoreSystem>();
        _renderSystem = std::make_unique<Internal::RenderingSystemGL>();
        _inputSystem = std::make_unique<Internal::InputSystem>();
        _audioSystem = std::make_unique<Internal::AudioSystem>();
        _sceneManagementSystem = std::make_unique<Internal::SceneSystem>();

        _coreSystem->onWindowResize.AddListener([this](auto size) {
            screenSize = size;
        });

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
        SystemInit(_renderSystem, configuration, _coreSystem.get());
        SystemInit(_inputSystem, configuration.input, _coreSystem.get());
        SystemInit(_audioSystem, configuration.audio, _coreSystem.get());
        SystemInit(_sceneManagementSystem, configuration.game, this, _coreSystem.get());

        DebugLog("All systems initialized");

#ifdef __EMSCRIPTEN__
        _coreSystem->onShutdown += [this]() {
            for (auto &s : _systems) {
                s->Quit();
            }
            DebugLog("Quit Application");
        };
        return _coreSystem->Execute();
#else
        auto result = _coreSystem->Execute();
        if (result < 0) {
            DebugLogError("Application executed with an error");
        }

        for (auto &_system: _systems) {
            _system->Quit();
        }

        DebugLog("Quit Application");
        return result;
#endif
    }

    int Application::GetWindowFlags() const {
        return _coreSystem->GetWindowFlags() |
               _renderSystem->GetWindowFlags();
    }

    int Application::GetInitFlags() const {
        return _coreSystem->GetInitFlags() |
               _audioSystem->GetInitFlags();
    }

    const Vector2Int &Application::GetScreenSize() const {
        return screenSize;
    }

    float Application::GetScreenAspect() const {
        return (float) screenSize.x / (float) screenSize.y;
    }
}// namespace Harpia