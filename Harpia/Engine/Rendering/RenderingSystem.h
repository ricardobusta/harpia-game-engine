//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEM_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEM_H

#include "IApplicationSystem.h"
#include "GlobalDefines.h"
#include <list>
#include "InternalDefines.h"

namespace Harpia::Internal {
class RenderingSystem : public Internal::IApplicationSystem {
    public:
        int Initialize(GameConfiguration &configuration, Internal::CoreSystem *coreSystem);

        virtual void RenderFrame() = 0;

        void FetchCameras(Scene * scene);
    private:
        virtual int RenderingInitialize() = 0;

        int GetInitFlags() override;

        void FetchCameras(const std::list<Object*> &objects);

        std::list<CameraComponent*> _cameras;
    protected:
        SDL_Window *_window = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEM_H
