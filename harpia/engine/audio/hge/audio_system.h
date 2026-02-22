//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIO_SYSTEM_H
#define HARPIAGAMEENGINE_AUDIO_SYSTEM_H

#include "audio_asset.h"
#include "hge/asset_container.h"
#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include "mix_types.h"
#include "music_asset.h"

namespace Harpia::Internal {
    class AudioSystem : public IApplicationSystem {
    private:
        AssetContainer<AudioAsset> _loadedAudios;
        AssetContainer<MusicAsset> _loadedMusics;
        MIX_Mixer *_mixer = nullptr;
        MIX_Track *_musicTrack = nullptr;

    public:
        AudioAsset *LoadAudio(const std::string &path);
        void ReleaseAudio(AudioAsset *audio);
        void PlayAudio(AudioAsset *audio) const;

        MusicAsset *LoadMusic(const std::string &path);
        void ReleaseMusic(MusicAsset *music);
        void PlayMusic(MusicAsset *music) const;
        void SetMusicVolume(float volume = 1) const;
        void PauseMusic() const;
        void ResumeMusic() const;
        void SetMusicPosition(float positionInSeconds) const;
        [[nodiscard]] bool IsMusicPaused() const;

        int Initialize(const AudioConfiguration &config, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;

    private:
        void DeleteAudio(AudioAsset *audio) const;
        void ReleaseAllUsages(AudioAsset *audio) const;
        void DeleteMusic(MusicAsset *music) const;
        void ReleaseAllUsages(MusicAsset *music) const;
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_AUDIO_SYSTEM_H
