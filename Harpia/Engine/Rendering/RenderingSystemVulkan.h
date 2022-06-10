//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEMVULKAN_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEMVULKAN_H

#include "RenderingSystem.h"

namespace Harpia::Internal {
    class RenderingSystemVulkan : public RenderingSystem {
    private:
        void RenderFrame() override;
        int RenderingInitialize() override;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEMVULKAN_H
