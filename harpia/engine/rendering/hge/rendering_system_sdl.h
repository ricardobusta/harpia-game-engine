//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_SDL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_SDL_H

#include "rendering_system.h"

namespace Harpia::Internal {

    class RenderingSystemSDL : public RenderingSystem {
    private:
        SDL_Surface *_surface = nullptr;
        Color *_clearColor = nullptr;
    private:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;
        int RenderingInitialize() override;
    };

} // Harpia::Internal

#endif //HARPIAGAMEENGINE_RENDERING_SYSTEM_SDL_H
