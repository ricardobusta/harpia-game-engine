//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#include "hge/shader_asset.h"
#include "hge/rendering_system.h"
#include "hge/debug.h"

namespace Harpia {
    ShaderAsset::ShaderAsset(Internal::RenderingSystem *renderingSystem) {
        _renderingSystem = renderingSystem;
    }

    void ShaderAsset::Release() {
        _renderingSystem->ReleaseShader(this);
        DebugLog("Shader released. Usages: %d", useCount);
    }
} // Harpia