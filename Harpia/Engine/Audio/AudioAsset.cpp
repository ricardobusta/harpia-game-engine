//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "AudioAsset.h"
#include "Application_Internal.h"
#include "AudioSystem.h"

namespace Harpia {
    void AudioAsset::Release(Internal::Application_Internal *application) {
        application->_audioSystem->ReleaseAudio(this);
    }
} // Harpia