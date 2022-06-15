//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MusicAsset.h"
#include "Application_Internal.h"
#include "AudioSystem.h"

namespace Harpia {
    void MusicAsset::Release() {
        _audioSystem->ReleaseMusic(this);
    }

    MusicAsset::MusicAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia