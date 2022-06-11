//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOASSET_H
#define HARPIAGAMEENGINE_AUDIOASSET_H

#include "Asset.h"
#include "MixTypes.h"
#include "InternalDefines.h"

namespace Harpia {
    class AudioAsset : public Asset {
    public:
        Mix_Chunk *ref;
    private:
        Internal::AudioSystem *_audioSystem;
    public:
        explicit AudioAsset(Internal::AudioSystem *audioSystem);
        AudioAsset() = delete;
        void Release() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOASSET_H
