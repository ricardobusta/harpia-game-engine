//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "AudioComponent.h"
#include "GlobalDefines.h"
#include "Internal/Application_Internal.h"
#include "AudioSystem.h"
#include "Debug.h"
#include "HarpiaAssert.h"

namespace Harpia {
    void AudioComponent::Play() {
        AssertNotNull(_audio);
        _audioSystem->PlayAudio(_audio);
    }

    void AudioComponent::SetAudioFile(const std::string &path) {
        if (_audio != nullptr) {
            _audioSystem->ReleaseAudio(_audio);
        }
        _audio = _audioSystem->LoadAudio(path);
    }

    void AudioComponent::Initialize_Internal(Application_Internal *applicationInternal) {
        _audioSystem = applicationInternal->_audioSystem;
    }
} // Harpia