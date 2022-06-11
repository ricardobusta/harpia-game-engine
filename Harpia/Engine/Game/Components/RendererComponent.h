//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERERCOMPONENT_H
#define HARPIAGAMEENGINE_RENDERERCOMPONENT_H

#include "Component.h"
#include "Renderer_Internal.h"

namespace Harpia {
    class RendererComponent : public Component, public Internal::Renderer_Internal {

    public:
        void SetMesh(MeshAsset *mesh);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_RENDERERCOMPONENT_H
