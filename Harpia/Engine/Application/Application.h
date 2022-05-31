//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include "Configuration.h"

#include <map>

class SDL_Window;

class SDL_Surface;

namespace Harpia::Engine {
    class OpenGLApplication;

    class Application {
    public:
        Configuration *configuration;
    protected:
        SDL_Window *_window = nullptr;
    private:
        int _result = -1;

        SDL_Surface *_surface = nullptr;

        std::map<char, int> * _keyMap;
    public:
        explicit Application();

        ~Application();

        int Execute();

    private:
        virtual int Initialize();

        virtual void FrameUpdate();

        void Quit();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
