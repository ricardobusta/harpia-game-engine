//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSYSTEM_H
#define HARPIAGAMEENGINE_AUDIOSYSTEM_H

#include <map>
#include <string>

#include "CoreSystem.h"
#include "Audio.h"
#include "Music.h"

namespace Harpia {
    class AudioConfiguration;

    class AudioSystem : public CoreSystem {
    public:
    private:
        std::map<std::string, Audio *> _loadedAudios;
        std::map<std::string, Music *> _loadedMusics;
    public:
        Audio *LoadAudio(const std::string &path);

        void ReleaseAudio(Audio *audio);

        Music *LoadMusic(const std::string &path);

        void ReleaseMusic(Music *music);

        int Initialize(AudioConfiguration &config);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    private:
        void ReleaseAllUsages(Audio *audio);
        void ReleaseAllUsages(Music *music);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSYSTEM_H
