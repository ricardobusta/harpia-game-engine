//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "MusicComponent.h"
#include "hge/Debug.h"
#include "hge/AudioSystem.h"
#include "hge/HarpiaAssert.h"
#include "hge/in/Application_Internal.h"

namespace Harpia {
    void MusicComponent::SetMusic(MusicAsset *music) {
        this->_music = music;
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