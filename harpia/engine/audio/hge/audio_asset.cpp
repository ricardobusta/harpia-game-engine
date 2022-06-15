//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "hge/audio_asset.h"
#include "hge/in/application_internal.h"
#include "hge/audio_system.h"

namespace Harpia {
    void AudioAsset::Release() {
        _audioSystem->ReleaseAudio(this);
    }

    AudioAsset::AudioAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia