//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "music_component.h"
#include "hge/audio_system.h"
#include "hge/debug.h"
#include "hge/harpia_assert.h"
#include "hge/in/application_internal.h"

namespace Harpia {
    void MusicComponent::SetMusic(MusicAsset *music) {
        this->_music = music;
    }

    void MusicComponent::Play() {
        AssertNotNull(_music);
        _audioSystem->PlayMusic(_music);
    }

    bool MusicComponent::IsPaused() const {
        return _audioSystem->IsMusicPaused();
    }

    void MusicComponent::Pause(bool pause) const {
        if (pause) {
            _audioSystem->PauseMusic();
        } else {
            _audioSystem->ResumeMusic();
        }
    }

    void MusicComponent::SetVolume(float volume) const {
        _audioSystem->SetMusicVolume(volume);
    }

    void MusicComponent::SetPosition(float positionInSeconds) const {
        _audioSystem->SetMusicPosition(positionInSeconds);
    }

    void MusicComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _audioSystem = applicationInternal->_audioSystem.get();
    }
}// namespace Harpia