//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOCOMPONENT_H
#define HARPIAGAMEENGINE_AUDIOCOMPONENT_H

#include <string>
#include "Component.h"
#include "GlobalDefines.h"

namespace Harpia {
    class AudioComponent : public Component {
    private:
        AudioAsset *audio = nullptr;
        AudioSystem *_audioSystem = nullptr;
    public:
        void Play();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOCOMPONENT_H
