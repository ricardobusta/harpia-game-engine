//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEMSDL_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEMSDL_H

#include "RenderingSystem.h"

namespace Harpia::Internal {

    class RenderingSystemSDL : public RenderingSystem {
    private:
        SDL_Surface *_surface = nullptr;
        Color * _clearColor;
    private:
        int GetWindowFlags() override;

        void RenderFrame() override;

        void Quit() override;

        int RenderingInitialize() override;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEMSDL_H
