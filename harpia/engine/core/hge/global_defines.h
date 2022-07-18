//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_GLOBALDEFINES_H
#define HARPIAGAMEENGINE_GLOBALDEFINES_H

#include <cstdint>

typedef uint32_t Uint32;
typedef uint64_t Uint64;

namespace Harpia {// Game/Application
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
    struct Color;
    class Time;
}// namespace Harpia

namespace Harpia {// Components
    class Component;
    class CameraComponent;
    class AudioComponent;
    class MusicComponent;
    class RendererComponent;
}// namespace Harpia

#endif//HARPIAGAMEENGINE_GLOBALDEFINES_H
