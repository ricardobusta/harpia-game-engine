//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOCOMPONENT_H
#define HARPIAGAMEENGINE_AUDIOCOMPONENT_H

#include <string>
#include "Component.h"
#include "GlobalDefines.h"
#include "Internal/InternalDefines.h"

namespace Harpia {
    class AudioComponent : public Component {
    private:
        AudioAsset *_audio = nullptr;
        Internal::AudioSystem *_audioSystem = nullptr;
    public:
        void SetAudioFile(const std::string &path);
        void Play();
    protected:
        void Initialize_Internal(Internal::Application_Internal * applicationInternal) override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOCOMPONENT_H
