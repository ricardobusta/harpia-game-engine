//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIO_COMPONENT_H
#define HARPIAGAMEENGINE_AUDIO_COMPONENT_H

#include "component.h"
#include "hge/global_defines.h"
#include "hge/internal_defines.h"
#include <string>

namespace Harpia {
    class AudioComponent : public Component {
    private:
        AudioAsset *_audio = nullptr;
        Internal::AudioSystem *_audioSystem = nullptr;

    public:
        void SetAudio(AudioAsset *audio);
        void Play();

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_AUDIO_COMPONENT_H
