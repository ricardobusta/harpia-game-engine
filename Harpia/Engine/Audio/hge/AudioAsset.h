//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOASSET_H
#define HARPIAGAMEENGINE_AUDIOASSET_H

#include "hge/Asset.h"
#include "MixTypes.h"
#include "hge/InternalDefines.h"

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

#endif //HARPIAGAMEENGINE_AUDIOASSET_H
