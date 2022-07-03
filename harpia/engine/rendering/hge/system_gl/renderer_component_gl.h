//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H

#include "hge/renderer_component.h"

namespace Harpia::Internal {
    class RendererComponentGL : public RendererComponent {
    public:
        MeshAssetGL *_mesh;
        MaterialAssetGL *_material;
    public:
        void SetMesh(MeshAsset *mesh) override;
        void SetMaterial(MaterialAsset *material) override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_GL_H
