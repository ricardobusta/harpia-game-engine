//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSOURCE_H
#define HARPIAGAMEENGINE_AUDIOSOURCE_H

#include <string>
#include "Component.h"
#include "GlobalDefines.h"

namespace Harpia {
    class AudioSource : public Component {
    private:
        AudioAsset *audio;
        AudioSystem *_audioSystem;
    public:
//        explicit AudioSource(const std::string &path);
//
//        ~AudioSource();
//
//        void Play();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSOURCE_H
