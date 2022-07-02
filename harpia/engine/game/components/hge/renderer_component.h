//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_H

#include "hge/component.h"
#include "hge/renderer_internal.h"

namespace Harpia {
    class RendererComponent : public Component, public Internal::Renderer_Internal {
    public:
        void SetMesh(MeshAsset *mesh);
        void SetMaterial(MaterialAsset *material);

    private:
        Transform *GetTransformInternal() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_H
