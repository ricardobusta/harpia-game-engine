//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "AudioSystem.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include "Debug.h"

namespace Harpia {
    int AudioSystem::Initialize(AudioConfiguration &config) {
        DebugLog("Init");
        auto result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        if (result < 0) {
            DebugLogError("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
            return result;
        }

        return 0;
    }

    int AudioSystem::GetInitFlags() {
        return SDL_INIT_AUDIO;
    }

    int AudioSystem::GetWindowFlags() {
        return 0;
    }

    void AudioSystem::Quit() {
        Mix_Quit();
        DebugLog("Quit");
    }

} // Harpia