//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "core_system.h"

#include "hge/configuration.h"
#include "hge/debug.h"
#include <SDL3/SDL.h>

namespace Harpia::Internal {
    int CoreSystem::Initialize(const Configuration &config, int InitFlags, int WindowFlags) {
        if (!SDL_Init(InitFlags)) {
            DebugLogError("SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return -1;
        }

        auto w = config.window.size.x;
        auto h = config.window.size.y;
        _window = SDL_CreateWindow(config.game.title.c_str(), w, h, WindowFlags);
        if (_window == nullptr) {
            DebugLogError("Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        if (config.window.overridePosition) {
            SDL_SetWindowPosition(_window, config.window.position.x, config.window.position.y);
        }

        SDL_SetWindowResizable(_window, config.window.resizeable);

        _time.deltaTime = 0;
        _time.now = CalculateNow();

        _fpsCap = (Uint64) config.game.frameRateCap;

        return 0;
    }

    int CoreSystem::Execute() {
        onInitialize.Invoke();

        _quit = false;
        SDL_Event e;

        while (true) {
            _frameStartTick = NowTick();
            auto now = CalculateNow();
            _time.deltaTime = now - _time.now;
            _time.now = now;
            onPreEvents.Invoke();

            while (SDL_PollEvent(&e) != 0) {
                HandleEvents(e);
            }

            if (_quit) {
                break;
            }

            onSceneChanges.Invoke();
            onUpdate.Invoke();
            onRenderStep.Invoke();
            onLateUpdate.Invoke();

            FrameDelay();
        }
        return 0;
    }

    void CoreSystem::HandleEvents(const SDL_Event &e) {
        switch (e.type) {
            case SDL_EVENT_QUIT:
                onQuit.Invoke();
                _quit = true;
                DebugLog("Requested to quit");
                break;
            case SDL_EVENT_TERMINATING:
                DebugLog("App terminating");
                break;
            case SDL_EVENT_LOW_MEMORY:
                DebugLogWarning("App low on memory. Free stuff.");
                break;
            case SDL_EVENT_WILL_ENTER_BACKGROUND:
                DebugLog("App will pause.");
                break;
            case SDL_EVENT_DID_ENTER_BACKGROUND:
                DebugLog("App paused.");
                break;
            case SDL_EVENT_WILL_ENTER_FOREGROUND:
                DebugLog("App will resume.");
                break;
            case SDL_EVENT_DID_ENTER_FOREGROUND:
                DebugLog("App resumed.");
                break;
            case SDL_EVENT_LOCALE_CHANGED:
                DebugLog("Device locale changed.");
                break;
            // Window events (now top-level in SDL3)
            case SDL_EVENT_WINDOW_SHOWN:
                break;
            case SDL_EVENT_WINDOW_HIDDEN:
                break;
            case SDL_EVENT_WINDOW_EXPOSED:
                break;
            case SDL_EVENT_WINDOW_MOVED:
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                onWindowResize.Invoke({e.window.data1, e.window.data2});
                break;
            case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
                break;
            case SDL_EVENT_WINDOW_MINIMIZED:
                break;
            case SDL_EVENT_WINDOW_MAXIMIZED:
                break;
            case SDL_EVENT_WINDOW_RESTORED:
                break;
            case SDL_EVENT_WINDOW_MOUSE_ENTER:
                break;
            case SDL_EVENT_WINDOW_MOUSE_LEAVE:
                break;
            case SDL_EVENT_WINDOW_FOCUS_GAINED:
                break;
            case SDL_EVENT_WINDOW_FOCUS_LOST:
                break;
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
                break;
            case SDL_EVENT_WINDOW_HIT_TEST:
                break;
            // Input events
            case SDL_EVENT_KEY_DOWN:
                onKeyDown.Invoke(e.key);
                break;
            case SDL_EVENT_KEY_UP:
                onKeyUp.Invoke(e.key);
                break;
            case SDL_EVENT_TEXT_EDITING:
                break;
            case SDL_EVENT_TEXT_INPUT:
                break;
            case SDL_EVENT_MOUSE_MOTION:
                onMouseMove.Invoke(e.motion);
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                onMouseButtonDown.Invoke(e.button);
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                onMouseButtonUp.Invoke(e.button);
                break;
            case SDL_EVENT_MOUSE_WHEEL:
                onMouseWheel.Invoke(e.wheel);
                break;
            // Joystick events
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                DebugLog("Joy Axis Motion");
                break;
            case SDL_EVENT_JOYSTICK_BALL_MOTION:
                DebugLog("Joy Ball Motion");
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                DebugLog("Joy Hat Motion");
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                DebugLog("Joy Button Down");
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                DebugLog("Joy Button Up");
                break;
            case SDL_EVENT_JOYSTICK_ADDED:
                DebugLog("Joy Device Added");
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                DebugLog("Joy Device Removed");
                break;
            case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
                DebugLog("Joy Battery Updated");
                break;
            // Gamepad events (formerly "Controller" in SDL2)
            case SDL_EVENT_GAMEPAD_AXIS_MOTION:
                DebugLog("Controller Axis Motion");
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                DebugLog("Controller Button Down");
                break;
            case SDL_EVENT_GAMEPAD_BUTTON_UP:
                DebugLog("Controller Button Up");
                break;
            case SDL_EVENT_GAMEPAD_ADDED:
                DebugLog("Controller Device Added");
                break;
            case SDL_EVENT_GAMEPAD_REMOVED:
                DebugLog("Controller Device Removed");
                break;
            case SDL_EVENT_GAMEPAD_REMAPPED:
                DebugLog("Controller Device Remapped");
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
                DebugLog("Controller Touchpad Down");
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
                DebugLog("Controller Touchpad Motion");
                break;
            case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
                DebugLog("Controller Touchpad Up");
                break;
            case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
                DebugLog("Controller Sensor Update");
                break;
            // Touch events
            case SDL_EVENT_FINGER_DOWN:
                DebugLog("Finger Down");
                break;
            case SDL_EVENT_FINGER_UP:
                DebugLog("Finger Up");
                break;
            case SDL_EVENT_FINGER_MOTION:
                DebugLog("Finger Motion");
                break;
            // Misc events
            case SDL_EVENT_CLIPBOARD_UPDATE:
                DebugLog("Clipboard Update");
                break;
            case SDL_EVENT_DROP_FILE:
                DebugLog("Drop File");
                break;
            case SDL_EVENT_DROP_TEXT:
                DebugLog("Drop Text");
                break;
            case SDL_EVENT_DROP_BEGIN:
                DebugLog("Drop Begin");
                break;
            case SDL_EVENT_DROP_COMPLETE:
                DebugLog("Drop Complete");
                break;
            case SDL_EVENT_AUDIO_DEVICE_ADDED:
                break;
            case SDL_EVENT_AUDIO_DEVICE_REMOVED:
                break;
            case SDL_EVENT_SENSOR_UPDATE:
                DebugLog("Sensor Update");
                break;
            case SDL_EVENT_RENDER_TARGETS_RESET:
                DebugLog("Targets Reset");
                break;
            case SDL_EVENT_RENDER_DEVICE_RESET:
                DebugLog("Device Reset");
                break;
            default:
                // Unknown event
                break;
        }
    }

    void CoreSystem::FrameDelay() const {
        if (_fpsCap == 0) {
            return;
        }

        auto frameLimitTime = 1000 / _fpsCap;
        auto frameTime = NowTick() - _frameStartTick;
        if (frameTime < frameLimitTime) {
            SDL_Delay(frameLimitTime - frameTime);
        }
    }

    float CoreSystem::CalculateNow() const { return _time.timeScale * (float) NowTick() / 1000.0f; }

    Uint64 CoreSystem::NowTick() const {
        return SDL_GetTicks();
    }

    int CoreSystem::GetInitFlags() {
        return SDL_INIT_VIDEO;
    }

    int CoreSystem::GetWindowFlags() {
        return 0;
    }

    void CoreSystem::Quit() {
        SDL_DestroyWindow(_window);
        _window = nullptr;

        SDL_Quit();
    }

    SDL_Window *CoreSystem::GetWindow() {
        return _window;
    }

    const Time *CoreSystem::GetTime() const {
        return &_time;
    }
}// namespace Harpia::Internal
