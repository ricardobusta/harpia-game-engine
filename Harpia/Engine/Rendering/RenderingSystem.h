//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEM_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEM_H

#include "CoreSystem.h"

class SDL_Window;

class SDL_Surface;

namespace Harpia {
    class GameConfiguration;
    class Color;

    class RenderingSystem : CoreSystem {
    public:
        int Initialize(GameConfiguration &configuration, SDL_Window *window);

        virtual void UpdateFrame();

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    private:
        virtual int RenderingInitialize();

    protected:
        Color *_clearColor;
        SDL_Window *_window = nullptr;
    private:
        SDL_Surface *_surface = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEM_H
