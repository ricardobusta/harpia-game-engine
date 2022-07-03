//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_GLOBALDEFINES_H
#define HARPIAGAMEENGINE_GLOBALDEFINES_H

union SDL_Event;
struct SDL_Surface;
struct SDL_KeyboardEvent;
class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

namespace Harpia { // Game/Application
    class Application;
    class Scene;
    class Object;
    class Configuration;
    class GameConfiguration;
    class InputConfiguration;
    class AudioConfiguration;
    class InputReader;
    class Color;
    class AudioAsset;
    class MusicAsset;
    class MaterialAsset;
    class MeshAsset;
    class TextureAsset;
    class ShaderAsset;
    class Asset;
    class Transform;
}

namespace Harpia { // Components
    class Component;
    class CameraComponent;
    class AudioComponent;
    class MusicComponent;
    class RendererComponent;
}

#endif //HARPIAGAMEENGINE_GLOBALDEFINES_H
