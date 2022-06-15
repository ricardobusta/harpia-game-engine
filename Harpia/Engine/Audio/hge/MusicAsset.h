//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_MUSICASSET_H
#define HARPIAGAMEENGINE_MUSICASSET_H

#include "hge/Asset.h"
#include "hge/InternalDefines.h"
#include "hge/MixTypes.h"

namespace Harpia {
    class MusicAsset : public Asset {
    public:
        Mix_Music *ref = nullptr;
    private:
        Internal::AudioSystem *_audioSystem = nullptr;
    public:
        explicit MusicAsset(Internal::AudioSystem *audioSystem);
        MusicAsset() = delete;
        void Release() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MUSICASSET_H
