//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CORE_H
#define HARPIAGAMEENGINE_CORE_H

#include "Engine/Configuration.h"
#include "SDL.h"

namespace Harpia::Engine {
    class Core {
    private:
        SDL_Window *_window = nullptr;
        SDL_Surface *_surface = nullptr;
    public:
        int Start();

        void Quit();

        void Draw();
    };
}

#endif //HARPIAGAMEENGINE_CORE_H
