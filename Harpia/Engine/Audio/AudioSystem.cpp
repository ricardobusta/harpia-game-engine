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
        for (const auto &m: _loadedMusics) {
            ReleaseAllUsages(m.second);
        }
        Mix_Quit();
        DebugLog("Quit");
    }

    AudioAsset *AudioSystem::LoadAudio(const std::string &path) {
        auto it = _loadedAudios.find(path);
        if (it != _loadedAudios.end()) {
            it->second->useCount++;
            DebugLog("Loading existing audio %s use count: %d", path.c_str(), it->second->useCount);
            return it->second;
        }
        auto ref = Mix_LoadWAV(path.c_str());
        if (ref == nullptr) {
            DebugLogError("AudioAsset %s was not loaded. SDL_mixer Error: %s", path.c_str(), Mix_GetError());
            return nullptr;
        }
        auto audio = new AudioAsset();
        audio->ref = ref;
        audio->path = path;
        audio->useCount = 1;
        _loadedAudios[path] = audio;
        DebugLog("Loading new audio %s use count: %d", path.c_str(), audio->useCount);
        return audio;
    }

    void AudioSystem::ReleaseAudio(AudioAsset *audio) {
        if (audio == nullptr) {
            DebugLogError("AudioAsset reference was null.");
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
            Mix_FreeChunk(audio->ref);
            delete audio;
        }
    }

    void AudioSystem::ReleaseAllUsages(AudioAsset *audio) {
        DebugLogWarning("AudioAsset with remaining %d uses on System Quit: %s", audio->useCount, audio->path.c_str());
        audio->useCount = 0;
        ReleaseAudio(audio);
    }

    MusicAsset *AudioSystem::LoadMusic(const std::string &path) {
        auto it = _loadedMusics.find(path);
        if (it != _loadedMusics.end()) {
            it->second->useCount++;
            return it->second;
        }
        auto ref = Mix_LoadMUS(path.c_str());
        if (ref == nullptr) {
            DebugLogError("MusicAsset %s was not loaded. SDL_mixer Error: %s", path.c_str(), Mix_GetError());
            return nullptr;
        }
        auto music = new MusicAsset();
        music->ref = ref;
        music->path = path;
        music->useCount = 1;
        _loadedMusics[path] = music;
        return music;
    }

    int AudioSystem::PlayMusic(MusicAsset *music) {
        return Mix_PlayMusic(music->ref, 0);
    }

    void AudioSystem::PauseMusic() {
        Mix_PauseMusic();
    }

    void AudioSystem::ResumeMusic() {
        Mix_ResumeMusic();
    }

    bool AudioSystem::IsMusicPaused(){
        return Mix_PausedMusic();
    }

    void AudioSystem::ReleaseMusic(MusicAsset *music) {
        if (music == nullptr) {
            DebugLogError("MusicAsset reference was null.");
            return;
        }

        auto it = _loadedMusics.find(music->path);
        if (it == _loadedMusics.end()) {
            DebugLogError("Trying to release music %s, but music was not loaded.", music->path.c_str());
            return;
        }

        it->second->useCount--;
        if (it->second->useCount <= 0) {
            _loadedMusics.erase(music->path);
            Mix_FreeMusic(music->ref);
            delete music;
        }
    }

    void AudioSystem::ReleaseAllUsages(MusicAsset *music) {
        DebugLogWarning("MusicAsset with remaining %d uses on System Quit: %s", music->useCount, music->path.c_str());
        music->useCount = 0;
        ReleaseMusic(music);
    }

    void AudioSystem::PlayAudio(AudioAsset *audio) {
        Mix_PlayChannel(-1, audio->ref, 0);
    }
}
// Harpia