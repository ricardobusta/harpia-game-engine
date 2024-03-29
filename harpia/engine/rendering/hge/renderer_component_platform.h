//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/07/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_PLATFORM_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_PLATFORM_H

#include "hge/internal_defines.h"

namespace Harpia::Internal {
    class RendererComponentPlatform {
    public:
        virtual ~RendererComponentPlatform() = default;
        virtual void SetMesh(MeshAsset *mesh) = 0;
        virtual void SetMaterial(MaterialAsset *material) = 0;
        virtual const MaterialAsset *GetMaterial() = 0;
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_PLATFORM_H
