//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include <map>

#include "Configuration.h"
#include "KeyState.h"

class SDL_Window;

namespace Harpia {
    class OpenGLApplication;

    class Renderer;

    class Input;

    class Application {
    public:
        Configuration *configuration = nullptr;
    private:
        bool _createdWithSuccess = false;
        int _result = -1;

        std::map<int, KeyState> _keyMap;
        std::list<int> _dirtyKeys;

        SDL_Window *_window = nullptr;
        Renderer *_renderer = nullptr;
        Input *_input = nullptr;
    public:
        explicit Application(Renderer *renderer);

        ~Application();

        int Execute();

    private:
        int Initialize();

        void Quit();

        void CleanKeyState();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
