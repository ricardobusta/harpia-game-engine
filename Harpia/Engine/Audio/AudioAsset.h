//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOASSET_H
#define HARPIAGAMEENGINE_AUDIOASSET_H

#include "Asset.h"
#include "MixTypes.h"

namespace Harpia {
    class AudioAsset : public Asset {
    public:
        Mix_Chunk *ref;

        void Release(Internal::Application_Internal *application) override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOASSET_H
