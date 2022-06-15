//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "hge/AudioAsset.h"
#include "hge/in/Application_Internal.h"
#include "hge/AudioSystem.h"

namespace Harpia {
    void AudioAsset::Release() {
        _audioSystem->ReleaseAudio(this);
    }

    AudioAsset::AudioAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia