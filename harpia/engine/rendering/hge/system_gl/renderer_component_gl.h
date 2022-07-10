//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H

#include "hge/internal_defines.h"
#include "hge/renderer_component_platform.h"

namespace Harpia::Internal {
    class RendererComponentGL : public RendererComponentPlatform {
    public:
        MeshAssetGL *_mesh = nullptr;
        MaterialAssetGL *_material = nullptr;

        RendererComponent_Internal *_renderer = nullptr;
        RenderingSystemGL *_renderingSystem = nullptr;

    public:
        void SetMesh(MeshAsset *mesh) override;
        void SetMaterial(MaterialAsset *material) override;
        const MaterialAsset *GetMaterial() override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H
