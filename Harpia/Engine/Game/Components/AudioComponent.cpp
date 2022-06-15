//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "AudioComponent.h"
#include "Application_Internal.h"
#include "AudioSystem.h"
#include "Debug.h"
#include "HarpiaAssert.h"

namespace Harpia {
    void AudioComponent::Play() {
        AssertNotNull(_audio);
        _audioSystem->PlayAudio(_audio);
    }

    void AudioComponent::SetAudio(AudioAsset *audio) {
        _audio = audio;
    }

    void AudioComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _audioSystem = applicationInternal->_audioSystem;
    }
} // Harpia