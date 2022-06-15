//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "hge/MaterialAsset.h"
#include "hge/in/Application_Internal.h"
#include "hge/RenderingSystem.h"

namespace Harpia {
    void MaterialAsset::Release() {

    }

    MaterialAsset::MaterialAsset(Internal::RenderingSystem *renderingSystem) {
        this->_renderingSystem = renderingSystem;
    }

    void MaterialAsset::SetShader(ShaderAsset *shader) {
        _shader = shader;
    }

    void MaterialAsset::SetColor(const Color &color) {
        this->color = color;
    }
} // Harpia