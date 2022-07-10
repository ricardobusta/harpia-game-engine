//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_H

#include "hge/component.h"
#include "hge/renderer_component_internal.h"

namespace Harpia {
    class RendererComponent : public Component, public Internal::RendererComponent_Internal {
    public:
        virtual void SetMesh(MeshAsset *mesh);
        virtual void SetMaterial(MaterialAsset *material);
        virtual const MaterialAsset *GetMaterial() const;

    private:
        Transform *GetTransformInternal() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_H
