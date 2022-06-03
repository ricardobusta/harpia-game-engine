//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include <map>

#include "Configuration.h"
#include "KeyState.h"

class SDL_Window;

class SDL_Surface;

namespace Harpia {
    class OpenGLApplication;

    class Renderer;

    class Input;

    class Application {
    public:
        Configuration *configuration;
    protected:
        SDL_Window *_window = nullptr;
    private:
        int _result = -1;

        SDL_Surface *_surface = nullptr;

        std::map<int, KeyState> _keyMap;
        std::list<int> _dirtyKeys;

        Renderer *_renderer;
        Input *_input;
    public:
        explicit Application(Renderer *renderer);

        ~Application();

        int Execute();

    private:
        virtual int Initialize();

        virtual void FrameUpdate();

        void Quit();

        void CleanKeyState();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
