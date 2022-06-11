//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEM_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEM_H

#include "IApplicationSystem.h"
#include <list>
#include "InternalDefines.h"

namespace Harpia::Internal {
    class RenderingSystem : public Internal::IApplicationSystem {
    protected:
        std::list<Camera_Internal *> _cameras;
        SDL_Window *_window = nullptr;
    public:
        int Initialize(GameConfiguration &configuration, Internal::CoreSystem *coreSystem);
        virtual void RenderFrame() = 0;
        void AddCamera(Camera_Internal *camera);
        virtual ~RenderingSystem() = default;
    private:
        virtual int RenderingInitialize() = 0;
        int GetInitFlags() override;
    };

} // Harpia::Internal

#endif //HARPIAGAMEENGINE_RENDERINGSYSTEM_H
