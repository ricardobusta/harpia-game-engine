//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "MaterialAsset.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"

namespace Harpia {
    void MaterialAsset::Release(Internal::Application_Internal *application) {
        application->_renderSystem->ReleaseMaterial(this);
    }
} // Harpia