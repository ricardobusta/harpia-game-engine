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
        for (const auto &a: _loadedAudios) {
            ReleaseAllUsages(a.second);
        }
        Mix_Quit();
        DebugLog("Quit");
    }

    Audio *AudioSystem::LoadAudio(const std::string &path) {
        auto it = _loadedAudios.find(path);
        if (it != _loadedAudios.end()) {
            it->second->useCount++;
            return it->second;
        }
        auto audio = new Audio();
        audio->path = path;
        audio->useCount = 1;
        _loadedAudios[path] = audio;
    }

    void AudioSystem::ReleaseAudio(Audio *audio) {
        if (audio == nullptr) {
            DebugLogError("Audio reference was null.");
            return;
        }

        auto it = _loadedAudios.find(audio->path);
        if (it == _loadedAudios.end()) {
            DebugLogError("Trying to release audio %s, but audio was not loaded.", audio->path.c_str());
            return;
        }

        it->second->useCount--;
        if (it->second->useCount <= 0) {
            _loadedAudios.erase(audio->path);
            delete audio;
        }
    }

    void AudioSystem::ReleaseAllUsages(Audio *audio) {
        DebugLogWarning("Audio with remaining %d uses on System Quit: %s", audio->useCount, audio->path.c_str());
        audio->useCount = 0;
        ReleaseAudio(audio);
    }
}
// Harpia