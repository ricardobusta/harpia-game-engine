//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/audio_component.h"
#include "hge/audio_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"
#include "hge/in/application_internal.h"

namespace Harpia {
    void AudioComponent::Play() {
        AssertNotNull(_audio);
        _audioSystem->PlayAudio(_audio);
    }

    void AudioComponent::SetAudio(AudioAsset *audio) {
        _audio = audio;
    }

    void AudioComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _audioSystem = applicationInternal->_audioSystem.get();
    }
}// namespace Harpia