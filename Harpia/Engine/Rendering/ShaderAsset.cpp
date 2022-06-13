//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#include "ShaderAsset.h"
#include "RenderingSystem.h"
#include "Debug.h"

namespace Harpia {
    ShaderAsset::ShaderAsset(Internal::RenderingSystem *renderingSystem) {
        _renderingSystem = renderingSystem;
    }

    void ShaderAsset::Release() {
        _renderingSystem->ReleaseShader(this);
        DebugLog("Shader released. Usages: %d", useCount);
    }
} // Harpia