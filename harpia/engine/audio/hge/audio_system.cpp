//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "audio_system.h"

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"

namespace Harpia::Internal {
    int AudioSystem::Initialize([[maybe_unused]] const AudioConfiguration &config, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init Audio");

        if (!MIX_Init()) {
            DebugLogError("SDL_mixer could not initialize! SDL Error: %s", SDL_GetError());
            return -1;
        }

        _mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (_mixer == nullptr) {
            DebugLogError("SDL_mixer could not open audio device! SDL Error: %s", SDL_GetError());
            return -1;
        }

        _musicTrack = MIX_CreateTrack(_mixer);
        if (_musicTrack == nullptr) {
            DebugLogError("SDL_mixer could not create music track! SDL Error: %s", SDL_GetError());
            return -1;
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
        if (_musicTrack != nullptr) {
            MIX_DestroyTrack(_musicTrack);
            _musicTrack = nullptr;
        }
        if (_mixer != nullptr) {
            MIX_DestroyMixer(_mixer);
            _mixer = nullptr;
        }
        MIX_Quit();
        DebugLog("Quit Audio");
    }

    void AudioSystem::PlayAudio(AudioAsset *audio) const {
        if (!MIX_PlayAudio(_mixer, audio->ref)) {
            DebugLogError("Audio could not be played. SDL Error: %s", SDL_GetError());
        }
    }

    AudioAsset *AudioSystem::LoadAudio(const std::string &path) {
        return _loadedAudios.LoadAsset(path, [this](auto p) -> std::unique_ptr<AudioAsset> {
            // predecode=true: fully decode into memory up-front, suitable for short sound effects
            auto ref = MIX_LoadAudio(_mixer, p.c_str(), true);
            if (ref == nullptr) {
                DebugLogError("AudioAsset %s was not loaded. SDL Error: %s", p.c_str(), SDL_GetError());
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
        MIX_DestroyAudio(audio->ref);
    }

    MusicAsset *AudioSystem::LoadMusic(const std::string &path) {
        return _loadedMusics.LoadAsset(path, [this](auto p) -> std::unique_ptr<MusicAsset> {
            // predecode=false: stream from disk, suitable for long music tracks
            auto ref = MIX_LoadAudio(_mixer, p.c_str(), false);
            if (ref == nullptr) {
                DebugLogError("MusicAsset %s was not loaded. SDL Error: %s", p.c_str(), SDL_GetError());
                return nullptr;
            }
            auto music = std::make_unique<MusicAsset>(this);
            music->ref = ref;
            return music;
        });
    }

    void AudioSystem::PlayMusic(MusicAsset *music) const {
        MIX_SetTrackAudio(_musicTrack, music->ref);
        SDL_PropertiesID props = SDL_CreateProperties();
        SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);
        if (!MIX_PlayTrack(_musicTrack, props)) {
            DebugLogError("Music could not be played. SDL Error: %s", SDL_GetError());
        }
        SDL_DestroyProperties(props);
    }

    void AudioSystem::SetMusicVolume(float volume) const {
        MIX_SetTrackGain(_musicTrack, volume);
    }

    void AudioSystem::PauseMusic() const {
        MIX_PauseTrack(_musicTrack);
    }

    void AudioSystem::ResumeMusic() const {
        MIX_ResumeTrack(_musicTrack);
    }

    bool AudioSystem::IsMusicPaused() const {
        return MIX_TrackPaused(_musicTrack);
    }

    void AudioSystem::SetMusicPosition(float positionInSeconds) const {
        Sint64 frames = MIX_TrackMSToFrames(_musicTrack, (Sint64) (positionInSeconds * 1000.0f));
        if (!MIX_SetTrackPlaybackPosition(_musicTrack, frames)) {
            DebugLogError("Music position not set. SDL Error: %s", SDL_GetError());
        }
    }

    void AudioSystem::ReleaseMusic(MusicAsset *music) {
        _loadedMusics.ReleaseAsset(music, [this](auto m) {
            DeleteMusic(m);
        });
    }

    void AudioSystem::DeleteMusic(MusicAsset *music) const {
        MIX_DestroyAudio(music->ref);
    }

    void AudioSystem::ReleaseAllUsages([[maybe_unused]] AudioAsset *audio) const {}
    void AudioSystem::ReleaseAllUsages([[maybe_unused]] MusicAsset *music) const {}
}// namespace Harpia::Internal
