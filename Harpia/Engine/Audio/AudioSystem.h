//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSYSTEM_H
#define HARPIAGAMEENGINE_AUDIOSYSTEM_H

#include <map>
#include <string>

#include "CoreSystem.h"
#include "Audio.h"

namespace Harpia {
    class AudioConfiguration;

    class AudioSystem : public CoreSystem {
    public:
    private:
        std::map<std::string, Audio *> _loadedAudios;
    public:
        Audio *LoadAudio(const std::string &path);

        void ReleaseAudio(Audio *audio);

        int Initialize(AudioConfiguration &config);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    private:
        void ReleaseAllUsages(Audio *audio);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSYSTEM_H
