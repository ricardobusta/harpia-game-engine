//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_GLOBALDEFINES_H
#define HARPIAGAMEENGINE_GLOBALDEFINES_H

union SDL_Event;
struct SDL_Surface;
struct SDL_KeyboardEvent;

class SDL_Window;

namespace Harpia {
    class AudioSystem;

    class CoreSystem;

    class InputSystem;

    class RenderingSystem;

    class SceneManagementSystem;

    class Application;

    class Scene;

    class Object;

    class Configuration;

    class GameConfiguration;
    class InputConfiguration;
    class RenderingConfiguration;
    class Color;

    static Application *app;
}

#endif //HARPIAGAMEENGINE_GLOBALDEFINES_H
