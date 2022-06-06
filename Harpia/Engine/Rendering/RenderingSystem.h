//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEM_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEM_H

#include "IApplicationSystem.h"
#include "GlobalDefines.h"

namespace Harpia {
    class RenderingSystem : IApplicationSystem {
    public:
        int Initialize(GameConfiguration &configuration, CoreSystem *coreSystem);

        virtual void UpdateFrame();

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

    private:
        virtual int RenderingInitialize();

    protected:
        Color *_clearColor = nullptr;
        SDL_Window *_window = nullptr;
    private:
        SDL_Surface *_surface = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEM_H
