//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "audio_system.h"

#include <SDL.h>
#include <SDL_mixer.h>

#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"

namespace Harpia::Internal {
    int AudioSystem::Initialize([[maybe_unused]] const AudioConfiguration &config, CoreSystem *coreSystem) const {
        AssertNotNull(coreSystem);

        DebugLog("Init Audio");
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
        _loadedAudios.Clear([this](auto a) { DeleteAudio(a); });
        _loadedMusics.Clear([this](auto m) { DeleteMusic(m); });
        Mix_Quit();
        DebugLog("Quit Audio");
    }

    void AudioSystem::PlayAudio(AudioAsset *audio) const {
        if (Mix_PlayChannel(-1, audio->ref, 0) < 0) {
            DebugLogError("Audio could not be played. Mix_Error: %s", Mix_GetError());
        }
    }

    AudioAsset *AudioSystem::LoadAudio(const std::string &path) {
        return _loadedAudios.LoadAsset(path, [this](auto p) -> std::unique_ptr<AudioAsset> {
            auto ref = Mix_LoadWAV(p.c_str());
            if (ref == nullptr) {
                DebugLogError("AudioAsset %s was not loaded. SDL_mixer Error: %s", p.c_str(), Mix_GetError());
                return nullptr;
            }
            auto audio = std::make_unique<AudioAsset>(this);
            audio->ref = ref;
            return audio;
        });
    }

    void AudioSystem::ReleaseAudio(AudioAsset *audio) {
        _loadedAudios.ReleaseAsset(audio, [this](auto a) {
            DeleteAudio(a);
        });
    }

    void AudioSystem::DeleteAudio(AudioAsset *audio) const {
        Mix_FreeChunk(audio->ref);
    }

    MusicAsset *AudioSystem::LoadMusic(const std::string &path) {
        return _loadedMusics.LoadAsset(path, [this](auto p) -> std::unique_ptr<MusicAsset> {
            auto ref = Mix_LoadMUS(p.c_str());
            if (ref == nullptr) {
                DebugLogError("MusicAsset %s was not loaded. SDL_mixer Error: %s", p.c_str(), Mix_GetError());
                return nullptr;
            }
            auto music = std::make_unique<MusicAsset>(this);
            music->ref = ref;
            return music;
        });
    }

    void AudioSystem::PlayMusic(MusicAsset *music) const {
        if (Mix_PlayMusic(music->ref, -1) < 0) {
            DebugLogError("Music could not be played. Mix_Error: %s", Mix_GetError());
        }
    }

    void AudioSystem::SetMusicVolume(float volume) const {
        Mix_VolumeMusic((int) (volume * MIX_MAX_VOLUME));
    }

    void AudioSystem::PauseMusic() const {
        Mix_PauseMusic();
    }

    void AudioSystem::ResumeMusic() const {
        Mix_ResumeMusic();
    }

    bool AudioSystem::IsMusicPaused() const {
        return Mix_PausedMusic() == SDL_TRUE;
    }

    void AudioSystem::SetMusicPosition(float positionInSeconds) const {
        if(Mix_SetMusicPosition((double)positionInSeconds)<0){
            DebugLogError("Music position not set. Mix_Error: %s", Mix_GetError());
        }
    }

    void AudioSystem::ReleaseMusic(MusicAsset *music) {
        _loadedMusics.ReleaseAsset(music, [this](auto m) {
            DeleteMusic(m);
        });
    }

    void AudioSystem::DeleteMusic(MusicAsset *music) const {
        Mix_FreeMusic(music->ref);
    }
}// namespace Harpia::Internal