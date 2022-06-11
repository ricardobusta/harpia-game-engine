//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_ASSET_H
#define HARPIAGAMEENGINE_ASSET_H

#include <string>
#include "InternalDefines.h"

namespace Harpia {
    class Asset {
    public:
        int useCount = 0;
        std::string path;

        virtual void Release() = 0;
    };
}

#endif //HARPIAGAMEENGINE_ASSET_H
