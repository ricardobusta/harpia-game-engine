//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INTERNALDEFINES_H
#define HARPIAGAMEENGINE_INTERNALDEFINES_H

#include "global_defines.h"

namespace Harpia::Internal {
    class IApplicationSystem;
    class Application_Internal;
    class Component_Internal;
    class CoreSystem;
    class AudioSystem;
    class ImageSystem;
    class InputSystem;
    class RenderingSystem;
    class SceneSystem;
    class Camera_Internal;
    class Scene_Internal;
    class Renderer_Internal;
}// namespace Harpia::Internal

namespace Harpia::Internal {// GL
    class RenderingSystemGL;
    class MeshAssetGL;
    class ShaderAssetGL;
    class MaterialAssetGL;
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_INTERNALDEFINES_H
