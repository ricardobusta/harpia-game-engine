//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#include "renderer_component.h"

namespace Harpia {
    Transform *RendererComponent::GetTransform() {
        return &GetObject()->transform;
    }
}// namespace Harpia