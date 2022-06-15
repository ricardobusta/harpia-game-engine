//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERERCOMPONENT_H
#define HARPIAGAMEENGINE_RENDERERCOMPONENT_H

#include "hge/Component.h"
#include "hge/Renderer_Internal.h"

namespace Harpia {
    class RendererComponent : public Component, public Internal::Renderer_Internal {
    public:
        void SetMesh(MeshAsset *mesh);
        void SetMaterial(MaterialAsset *material);
    private:
        Transform * GetTransformInternal() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_RENDERERCOMPONENT_H
