//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#include "texture_asset.h"
#include "hge/image_system.h"

namespace Harpia {
    TextureAsset::TextureAsset(SDL_Texture *ref, Internal::ImageSystem *imageSystem)
        : _imageSystem(imageSystem), ref(ref) {
    }

    void Harpia::TextureAsset::Release() {
        _imageSystem->ReleaseTexture(this);
    }
}// namespace Harpia