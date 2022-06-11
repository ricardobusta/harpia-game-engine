//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "MeshAsset.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"

namespace Harpia {
    void MeshAsset::Release(Internal::Application_Internal *application) {
        application->_renderSystem->ReleaseMesh(this);
    }
} // Harpia