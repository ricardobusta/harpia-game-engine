//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_ASSET_H
#define HARPIAGAMEENGINE_ASSET_H

#include "internal_defines.h"
#include <string>

namespace Harpia {
    class Asset {
    public:
        std::string path;

        virtual ~Asset() = default;
        virtual void Release() = 0;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_ASSET_H
