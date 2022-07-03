//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#ifndef HARPIAGAMEENGINE_IMAGE_SYSTEM_H
#define HARPIAGAMEENGINE_IMAGE_SYSTEM_H

#include "hge/asset_container.h"
#include "hge/global_defines.h"
#include "hge/i_application_system.h"
#include <map>
#include <string>
#include "hge/texture_asset.h"

namespace Harpia::Internal {
    class ImageSystem : public IApplicationSystem {
    public:
    private:
        AssetContainer<TextureAsset> _loadedTextures;
        SDL_Renderer *_renderer;

    public:
        int Initialize(CoreSystem *coreSystem);
        int GetWindowFlags() override;
        int GetInitFlags() override;
        void Quit() override;

        TextureAsset *LoadTexture(const std::string &path);
        void ReleaseTexture(TextureAsset *asset);

    private:
        void DeleteTexture(TextureAsset *asset);
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_IMAGE_SYSTEM_H
