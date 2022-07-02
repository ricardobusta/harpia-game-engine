//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#include "texture_asset.h"

namespace Harpia {
    TextureAsset::TextureAsset(Internal::ImageSystem *imageSystem)
        : _imageSystem(imageSystem) {
    }

    void Harpia::TextureAsset::Release() {
        //SDL_DestroyTexture( gTexture );
        //gTexture = NULL;
    }
}// namespace Harpia