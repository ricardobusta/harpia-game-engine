//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "audio_system.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include "hge/debug.h"
#include "hge/harpia_assert.h"
#include "hge/core_system.h"

namespace Harpia::Internal {
    int AudioSystem::Initialize(AudioConfiguration &config, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init");
        auto result = Mix_Init(MIX_INIT_OGG);
        if (result < 0) {
            DebugLogError("SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
            return result;
        }
        result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
        if (result < 0) {
            DebugLogError("SDL_mixer could not open audio! SDL_mixer Error: %s", Mix_GetError());
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
        for (const auto &kvp: _loadedAudios) {
            ReleaseAllUsages(kvp.second);
        }
        for (const auto &kvp: _loadedMusics) {
            ReleaseAllUsages(kvp.second);
        }
        Mix_Quit();
        DebugLog("Quit");
    }

    void AudioSystem::PlayAudio(AudioAsset *audio) {
        if (Mix_PlayChannel(-1, audio->ref, 0) < 0) {
            DebugLogError("Audio could not be played. Mix_Error: %s", Mix_GetError());
        }
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
        auto audio = new AudioAsset(this);
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
            DebugLog("Audio %s released", audio->path.c_str());
            _loadedAudios.erase(audio->path);
            DeleteAudio(audio);
        }
        DebugLog("Audio released. Usages: %d", it->second->useCount);
    }

    void AudioSystem::ReleaseAllUsages(AudioAsset *audio) {
        DebugLogWarning("AudioAsset with remaining %d uses on System Quit: %s", audio->useCount, audio->path.c_str());
        DeleteAudio(audio);
    }

    void AudioSystem::DeleteAudio(AudioAsset *audio) {
        Mix_FreeChunk(audio->ref);
        delete audio;
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
        auto music = new MusicAsset(this);
        music->ref = ref;
        music->path = path;
        music->useCount = 1;
        _loadedMusics[path] = music;
        return music;
    }

    void AudioSystem::PlayMusic(MusicAsset *music) {
        if (Mix_PlayMusic(music->ref, -1) < 0) {
            DebugLogError("Music could not be played. Mix_Error: %s", Mix_GetError());
        }
    }

    void AudioSystem::PauseMusic() {
        Mix_PauseMusic();
    }

    void AudioSystem::ResumeMusic() {
        Mix_ResumeMusic();
    }

    bool AudioSystem::IsMusicPaused() {
        return Mix_PausedMusic() == SDL_TRUE;
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
            DeleteMusic(music);
        }
        DebugLog("Music released. Usages: %d", it->second->useCount);
    }

    void AudioSystem::ReleaseAllUsages(MusicAsset *music) {
        DebugLogWarning("MusicAsset with remaining %d uses on System Quit: %s", music->useCount, music->path.c_str());
        DeleteMusic(music);
    }

    void AudioSystem::DeleteMusic(MusicAsset *music) {
        Mix_FreeMusic(music->ref);
        delete music;
    }
}
// Harpia