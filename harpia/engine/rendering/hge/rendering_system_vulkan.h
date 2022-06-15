//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_VULKAN_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_VULKAN_H

#include "rendering_system.h"

namespace Harpia::Internal {
    class RenderingSystemVulkan : public RenderingSystem {
    private:
        void RenderFrame() override;
        int RenderingInitialize() override;
    };

} // Harpia::Internal

#endif //HARPIAGAMEENGINE_RENDERING_SYSTEM_VULKAN_H
