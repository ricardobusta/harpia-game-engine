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
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOASSET_H
