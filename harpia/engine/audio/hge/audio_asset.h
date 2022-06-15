//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIO_ASSET_H
#define HARPIAGAMEENGINE_AUDIO_ASSET_H

#include "hge/asset.h"
#include "mix_types.h"
#include "hge/internal_defines.h"

namespace Harpia {
    class AudioAsset : public Asset {
    public:
        Mix_Chunk *ref = nullptr;
    private:
        Internal::AudioSystem *_audioSystem = nullptr;
    public:
        explicit AudioAsset(Internal::AudioSystem *audioSystem);
        AudioAsset() = delete;
        void Release() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIO_ASSET_H
