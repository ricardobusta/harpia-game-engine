//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INTERNALDEFINES_H
#define HARPIAGAMEENGINE_INTERNALDEFINES_H

#include "global_defines.h"

#define OUT

union SDL_Event;
struct SDL_Surface;
struct SDL_KeyboardEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;
struct SDL_MouseWheelEvent;
struct SDL_Window;

namespace Harpia::Internal {
    class IApplicationSystem;
    class Application_Internal;
    class Component_Internal;
    class CoreSystem;
    class AudioSystem;
    class InputSystem;
    class RenderingSystem;
    class SceneSystem;
    class Camera_Internal;
    class Scene_Internal;
    class RendererComponent_Internal;
    class RendererComponentPlatform;
    class UISystem;
    class GuiComponent_Internal;
}// namespace Harpia::Internal

namespace Harpia::Internal {// GL
    class RenderingSystemGL;
    class RendererComponentGL;
    class MeshAssetGL;
    class ShaderAssetGL;
    class TextureAssetGL;
    class MaterialAssetGL;
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_INTERNALDEFINES_H
