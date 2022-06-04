//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIO_H
#define HARPIAGAMEENGINE_AUDIO_H

#include "Asset.h"
#include "MixTypes.h"

namespace Harpia {

    class Audio : public Asset {
    public:
        Mix_Chunk *ref;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIO_H
