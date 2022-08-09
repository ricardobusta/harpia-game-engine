//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_MUSIC_COMPONENT_H
#define HARPIAGAMEENGINE_MUSIC_COMPONENT_H

#include "hge/component.h"
#include "hge/global_defines.h"
#include <string>

namespace Harpia {
    class MusicComponent : public Component {
    private:
        MusicAsset *_music = nullptr;
        Internal::AudioSystem *_audioSystem = nullptr;

    public:
        void SetMusic(MusicAsset *music);

        void Play();

        void Pause(bool pause) const;

        bool IsPaused() const;

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MUSIC_COMPONENT_H
