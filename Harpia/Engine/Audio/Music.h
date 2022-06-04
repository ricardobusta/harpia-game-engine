//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_MUSIC_H
#define HARPIAGAMEENGINE_MUSIC_H

#include "Asset.h"

#include "MixTypes.h"

namespace Harpia {

    class Music : public Asset {
    public:
        Mix_Music *ref;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_MUSIC_H
