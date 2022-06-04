//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_MUSICASSET_H
#define HARPIAGAMEENGINE_MUSICASSET_H

#include "Asset.h"

#include "MixTypes.h"

namespace Harpia {

    class MusicAsset : public Asset {
    public:
        Mix_Music *ref;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_MUSICASSET_H
