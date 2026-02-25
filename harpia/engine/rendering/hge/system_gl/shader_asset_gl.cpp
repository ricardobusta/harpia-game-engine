//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#include "shader_asset_gl.h"
#include "rendering_system_gl.h"
#include "hge/debug.h"

namespace Harpia::Internal {
    ShaderAssetGL::ShaderAssetGL(RenderingSystemGL *renderingSystem)
        : _renderingSystem(renderingSystem) {
    }
    void ShaderAssetGL::Release() {
        _renderingSystem->ReleaseShader(this);
        HDebugLog("Shader released.");
    }
}// namespace Harpia::Internal