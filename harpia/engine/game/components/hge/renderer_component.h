//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_RENDERER_COMPONENT_H

#include "hge/component.h"
#include "hge/renderer_internal.h"

namespace Harpia {
    class RendererComponent : public Component {
    public:
        virtual void SetMesh(MeshAsset *mesh) = 0;
        virtual void SetMaterial(MaterialAsset *material) = 0;

    private:
        Transform *GetTransform();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_RENDERER_COMPONENT_H
