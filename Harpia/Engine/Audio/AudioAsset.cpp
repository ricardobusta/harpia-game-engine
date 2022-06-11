//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "AudioAsset.h"
#include "Application_Internal.h"
#include "AudioSystem.h"

namespace Harpia {
    void AudioAsset::Release() {
        _audioSystem->ReleaseAudio(this);
    }

    AudioAsset::AudioAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia