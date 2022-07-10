//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXTURE_ASSET_H
#define HARPIAGAMEENGINE_TEXTURE_ASSET_H

#include "hge/asset.h"

namespace Harpia {
    enum TextureFilter{
        Nearest,
        Linear
    };
    enum TextureWrapMode{
        Repeat,
        Clamp,
        Mirror
    };
    class TextureAsset : public Asset {
    public:
        TextureFilter _filter = Linear;
        TextureWrapMode _wrapMode = Repeat;
    };
}// namespace Harpia


#endif//HARPIAGAMEENGINE_TEXTURE_ASSET_H
