//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIO_SYSTEM_H
#define HARPIAGAMEENGINE_AUDIO_SYSTEM_H

#include "audio_asset.h"
#include "hge/asset_container.h"
#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include "music_asset.h"

namespace Harpia::Internal {
    class AudioSystem : public IApplicationSystem {
    public:
    private:
        AssetContainer<AudioAsset> _loadedAudios;
        AssetContainer<MusicAsset> _loadedMusics;

    public:
        AudioAsset *LoadAudio(const std::string &path);
        void ReleaseAudio(AudioAsset *audio);
        void PlayAudio(AudioAsset *audio);

        MusicAsset *LoadMusic(const std::string &path);
        void ReleaseMusic(MusicAsset *music);
        void PlayMusic(MusicAsset *music);
        void SetMusicVolume(float volume = 1);
        void PauseMusic();
        void ResumeMusic();
        bool IsMusicPaused();

        int Initialize(const AudioConfiguration &config, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;

    private:
        void DeleteAudio(AudioAsset *audio);
        void ReleaseAllUsages(AudioAsset *audio);
        void DeleteMusic(MusicAsset *music);
        void ReleaseAllUsages(MusicAsset *music);
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_AUDIO_SYSTEM_H
