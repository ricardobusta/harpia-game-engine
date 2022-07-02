//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_INTERNAL_H
#define HARPIAGAMEENGINE_RENDERER_INTERNAL_H

#include "hge/internal_defines.h"

namespace Harpia::Internal {
    class Renderer_Internal {
    public:
        MeshAsset *_mesh = nullptr;
        MaterialAsset *_material = nullptr;

    public:
        virtual Transform *GetTransformInternal() = 0;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_RENDERER_INTERNAL_H
