//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/07/2022.
//

#ifndef HARPIAGAMEENGINE_IMAGE_SYSTEM_H
#define HARPIAGAMEENGINE_IMAGE_SYSTEM_H

#include "hge/global_defines.h"
#include "hge/i_application_system.h"

namespace Harpia::Internal {
    class ImageSystem : public IApplicationSystem {
    public:
    private:
    public:
        int Initialize();
        int GetWindowFlags() override;
        int GetInitFlags() override;
        void Quit() override;

        TextureAsset *LoadTexture();

    private:
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_IMAGE_SYSTEM_H
