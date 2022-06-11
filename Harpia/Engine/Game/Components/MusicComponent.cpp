//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "MusicComponent.h"
#include "Debug.h"
#include "AudioSystem.h"
#include "HarpiaAssert.h"
#include "Application_Internal.h"

namespace Harpia {
    void MusicComponent::SetMusicFile(const std::string &path) {
        if (_music != nullptr) {
            _audioSystem->ReleaseMusic(_music);
        }
        _music = _audioSystem->LoadMusic(path);
    }

    void MusicComponent::Play() {
        AssertNotNull(_music);
        _audioSystem->PlayMusic(_music);
    }

    bool MusicComponent::IsPaused() {
        return _audioSystem->IsMusicPaused();
    }

    void MusicComponent::Pause(bool pause) {
        if (pause) {
            _audioSystem->PauseMusic();
        } else {
            _audioSystem->ResumeMusic();
        }
    }

    void MusicComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _audioSystem = applicationInternal->_audioSystem;
    }
} // Harpia