//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "core_system.h"

#include "hge/configuration.h"
#include "hge/debug.h"
#include <SDL.h>

namespace Harpia::Internal {
    int CoreSystem::Initialize(const Configuration &config, int InitFlags, int WindowFlags) {
        if (auto result = SDL_Init(InitFlags); result < 0) {
            DebugLogError("SDL was not initialized. SDL_Error: %s", SDL_GetError());
            return result;
        }

        auto pos = config.window.overridePosition
                           ? config.window.position
                           : Vector2Int{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED};
        _window = SDL_CreateWindow(config.game.title.c_str(), pos.x, pos.y, config.window.size.x, config.window.size.y, WindowFlags);
        if (_window == nullptr) {
            DebugLogError("Window could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        SDL_SetWindowResizable(_window, config.window.resizeable ? SDL_TRUE : SDL_FALSE);

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
            case SDL_QUIT:
                onQuit.Invoke();
                _quit = true;
                DebugLog("Requested to quit");
                break;
            case SDL_APP_TERMINATING:
                DebugLog("App terminating");
                break;
            case SDL_APP_LOWMEMORY:
                DebugLogWarning("App low on memory. Free stuff.");
                break;
            case SDL_APP_WILLENTERBACKGROUND:
                DebugLog("App will pause.");
                break;
            case SDL_APP_DIDENTERBACKGROUND:
                DebugLog("App paused.");
                break;
            case SDL_APP_WILLENTERFOREGROUND:
                DebugLog("App will resume.");
                break;
            case SDL_APP_DIDENTERFOREGROUND:
                DebugLog("App resumed.");
                break;
            case SDL_LOCALECHANGED:
                DebugLog("Device locale changed.");
                break;
            case SDL_DISPLAYEVENT:
                DebugLog("Display changed.");
                break;
            case SDL_WINDOWEVENT:
                HandleWindowEvent(e);
                break;
            case SDL_KEYDOWN:
                onKeyDown.Invoke(e.key);
                break;
            case SDL_KEYUP:
                onKeyUp.Invoke(e.key);
                break;
            case SDL_TEXTEDITING:
                //DebugLog("Text editing");
                break;
            case SDL_TEXTINPUT:
                //DebugLog("Text input");
                break;
            case SDL_KEYMAPCHANGED:
                DebugLog("Input or keyboard layout changed.");
                break;
            case SDL_MOUSEMOTION:
                onMouseMove.Invoke(e.motion);
                break;
            case SDL_MOUSEBUTTONDOWN:
                onMouseButtonDown.Invoke(e.button);
                break;
            case SDL_MOUSEBUTTONUP:
                onMouseButtonUp.Invoke(e.button);
                break;
            case SDL_MOUSEWHEEL:
                onMouseWheel.Invoke(e.wheel);
                break;
            case SDL_JOYAXISMOTION:
                DebugLog("Joy Axis Motion");
                break;
            case SDL_JOYBALLMOTION:
                DebugLog("Joy Ball Motion");
                break;
            case SDL_JOYHATMOTION:
                DebugLog("Joy Hat Motion");
                break;
            case SDL_JOYBUTTONDOWN:
                DebugLog("Joy Button Down");
                break;
            case SDL_JOYBUTTONUP:
                DebugLog("Joy Button Up");
                break;
            case SDL_JOYDEVICEADDED:
                DebugLog("Joy Device Added");
                break;
            case SDL_JOYDEVICEREMOVED:
                DebugLog("Joy Device Removed");
                break;
            case SDL_JOYBATTERYUPDATED:
                DebugLog("Joy Battery Updated");
                break;
            case SDL_CONTROLLERAXISMOTION:
                DebugLog("Controller Axis Motion");
                break;
            case SDL_CONTROLLERBUTTONDOWN:
                DebugLog("Controller Button Down");
                break;
            case SDL_CONTROLLERBUTTONUP:
                DebugLog("Controller Button Up");
                break;
            case SDL_CONTROLLERDEVICEADDED:
                DebugLog("Controller Device Added");
                break;
            case SDL_CONTROLLERDEVICEREMOVED:
                DebugLog("Controller Device Removed");
                break;
            case SDL_CONTROLLERDEVICEREMAPPED:
                DebugLog("Controller Device Remapped");
                break;
            case SDL_CONTROLLERTOUCHPADDOWN:
                DebugLog("Controller Touchpad Down");
                break;
            case SDL_CONTROLLERTOUCHPADMOTION:
                DebugLog("Controller Touchpad Motion");
                break;
            case SDL_CONTROLLERTOUCHPADUP:
                DebugLog("Controller Touchpad Up");
                break;
            case SDL_CONTROLLERSENSORUPDATE:
                DebugLog("Controller Sensor Update");
                break;
            case SDL_FINGERDOWN:
                DebugLog("Finger Down");
                break;
            case SDL_FINGERUP:
                DebugLog("Finger Up");
                break;
            case SDL_FINGERMOTION:
                DebugLog("Finger Motion");
                break;
            case SDL_DOLLARGESTURE:
                DebugLog("Dollar Gesture");
                break;
            case SDL_DOLLARRECORD:
                DebugLog("Dollar Record");
                break;
            case SDL_MULTIGESTURE:
                DebugLog("Multi gesture");
                break;
            case SDL_CLIPBOARDUPDATE:
                DebugLog("Clipboard Update");
                break;
            case SDL_DROPFILE:
                DebugLog("Drop File");
                break;
            case SDL_DROPTEXT:
                DebugLog("Drop Text");
                break;
            case SDL_DROPBEGIN:
                DebugLog("Drop Begin");
                break;
            case SDL_DROPCOMPLETE:
                DebugLog("Drop Complete");
                break;
            case SDL_AUDIODEVICEADDED:
                //DebugLog("Audio Device Added");
                break;
            case SDL_AUDIODEVICEREMOVED:
                //DebugLog("Audio Device Removed");
                break;
            case SDL_SENSORUPDATE:
                DebugLog("Sensor Update");
                break;
            case SDL_RENDER_TARGETS_RESET:
                DebugLog("Targets Reset");
                break;
            case SDL_RENDER_DEVICE_RESET:
                DebugLog("Device Reset");
                break;
            default:
                // Unknown event
                break;
        }
    }

    void CoreSystem::HandleWindowEvent(const SDL_Event &e) {
        switch (e.window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                //DebugLog("Window %d shown", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                //DebugLog("Window %d hidden", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                //DebugLog("Window %d exposed", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_MOVED:
                //DebugLog("Window %d moved to %d,%d", e.window.windowID, e.window.data1, e.window.data2);
                break;
            case SDL_WINDOWEVENT_RESIZED:
                //DebugLog("Window %d resized to %dx%d", e.window.windowID, e.window.data1, e.window.data2);
                onWindowResize.Invoke({e.window.data1, e.window.data2});
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                //DebugLog("Window %d size changed to %dx%d", e.window.windowID, e.window.data1, e.window.data2);
                break;
            case SDL_WINDOWEVENT_MINIMIZED:
                //DebugLog("Window %d minimized", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_MAXIMIZED:
                //DebugLog("Window %d maximized", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_RESTORED:
                //DebugLog("Window %d restored", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_ENTER:
                //DebugLog("Mouse entered window %d", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_LEAVE:
                //DebugLog("Mouse left window %d", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                //DebugLog("Window %d gained keyboard focus", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_FOCUS_LOST:
                //DebugLog("Window %d lost keyboard focus", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_CLOSE:
                //DebugLog("Window %d closed", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_TAKE_FOCUS:
                //DebugLog("Window %d is offered a focus", e.window.windowID);
                break;
            case SDL_WINDOWEVENT_HIT_TEST:
                //DebugLog("Window %d has a special hit test", e.window.windowID);
                break;
            default:
                DebugLog("Window %d got unknown event %d", e.window.windowID, e.window.event);
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
        return SDL_GetTicks64();
    }

    int CoreSystem::GetInitFlags() {
        return SDL_INIT_VIDEO;
    }

    int CoreSystem::GetWindowFlags() {
        return SDL_WINDOW_SHOWN;
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