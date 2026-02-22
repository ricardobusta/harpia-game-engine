//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_MUSIC_ASSET_H
#define HARPIAGAMEENGINE_MUSIC_ASSET_H

#include "hge/asset.h"
#include "hge/internal_defines.h"
#include "hge/mix_types.h"

namespace Harpia {
    class MusicAsset : public Asset {
    public:
        MIX_Audio *ref = nullptr;
    private:
        Internal::AudioSystem *_audioSystem = nullptr;
    public:
        explicit MusicAsset(Internal::AudioSystem *audioSystem);
        MusicAsset() = delete;
        void Release() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MUSIC_ASSET_H
