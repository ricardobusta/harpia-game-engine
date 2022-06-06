//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEM_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEM_H

#include "IApplicationSystem.h"
#include "GlobalDefines.h"

namespace Harpia {
    class RenderingSystem : public IApplicationSystem {
    public:
        int Initialize(GameConfiguration &configuration, CoreSystem *coreSystem);

        virtual void RenderFrame() = 0;
    private:
        virtual int RenderingInitialize() = 0;

        int GetInitFlags() override;
    protected:
        SDL_Window *_window = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEM_H
