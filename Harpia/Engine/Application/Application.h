//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include "Configuration.h"

class SDL_Window;

class SDL_Surface;

namespace Harpia::Engine {
    class Application {
        int _result = -1;

        SDL_Window *_window = nullptr;
        SDL_Surface *_surface = nullptr;
    public:
        explicit Application(Configuration configuration);

        bool Execute();

        int Result();

    private:
        int Initialize();

        void Quit();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
