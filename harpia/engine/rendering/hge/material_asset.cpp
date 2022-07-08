//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "hge/material_asset.h"
#include "hge/in/application_internal.h"
#include "hge/rendering_system.h"

namespace Harpia {
    void MaterialAsset::Release() {
    }

    MaterialAsset::MaterialAsset(Internal::RenderingSystem *renderingSystem)
        : _renderingSystem(renderingSystem), _color(Color::white) {
    }

    void MaterialAsset::SetColor(const Color &color) {
        this->_color = color;
    }
}// namespace Harpia