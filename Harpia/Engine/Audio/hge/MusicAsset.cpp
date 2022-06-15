//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "hge/MusicAsset.h"
#include "hge/in/Application_Internal.h"
#include "hge/AudioSystem.h"

namespace Harpia {
    void MusicAsset::Release() {
        _audioSystem->ReleaseMusic(this);
    }

    MusicAsset::MusicAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia