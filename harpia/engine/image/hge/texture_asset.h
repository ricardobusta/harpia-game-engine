//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXTURE_ASSET_H
#define HARPIAGAMEENGINE_TEXTURE_ASSET_H

#include "hge/asset.h"

namespace Harpia {
    class TextureAsset : public Asset {
    public:
    private:
        Internal::ImageSystem *_imageSystem = nullptr;

    public:
        explicit TextureAsset(Internal::ImageSystem *imageSystem);
        TextureAsset() = delete;
        void Release() override;
    };
}// namespace Harpia


#endif//HARPIAGAMEENGINE_TEXTURE_ASSET_H
