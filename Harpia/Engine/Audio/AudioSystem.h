//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSYSTEM_H
#define HARPIAGAMEENGINE_AUDIOSYSTEM_H

#include <map>
#include <string>

#include "CoreSystem.h"
#include "AudioAsset.h"
#include "MusicAsset.h"

namespace Harpia {
    class AudioConfiguration;

    class AudioSystem : public CoreSystem {
    public:
    private:
        std::map<std::string, AudioAsset *> _loadedAudios;
        std::map<std::string, MusicAsset *> _loadedMusics;
    public:
        AudioAsset *LoadAudio(const std::string &path);

        void ReleaseAudio(AudioAsset *audio);

        void PlayAudio(AudioAsset *audio);

        MusicAsset *LoadMusic(const std::string &path);

        void ReleaseMusic(MusicAsset *music);

        int PlayMusic(MusicAsset *music);

        void PauseMusic();

        void ResumeMusic();

        bool IsMusicPaused();

        int Initialize(AudioConfiguration &config);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

    private:
        void ReleaseAllUsages(AudioAsset *audio);

        void ReleaseAllUsages(MusicAsset *music);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSYSTEM_H
