//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "MaterialAsset.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"

namespace Harpia {
    void MaterialAsset::Release() {

    }

    MaterialAsset::MaterialAsset(Internal::RenderingSystem *renderingSystem) {
        this->_renderingSystem = renderingSystem;
    }

    void MaterialAsset::SetShader(ShaderAsset *shader) {
        _shader = shader;
    }
} // Harpia