//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "hge/music_asset.h"
#include "hge/in/application_internal.h"
#include "hge/audio_system.h"

namespace Harpia {
    void MusicAsset::Release() {
        _audioSystem->ReleaseMusic(this);
    }

    MusicAsset::MusicAsset(Internal::AudioSystem *audioSystem) {
        _audioSystem = audioSystem;
    }
} // Harpia