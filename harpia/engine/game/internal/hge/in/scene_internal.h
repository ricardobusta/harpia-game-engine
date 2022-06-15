//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_INTERNAL_H
#define HARPIAGAMEENGINE_SCENE_INTERNAL_H

#include <list>
#include "hge/internal_defines.h"

namespace Harpia::Internal {
    class Scene_Internal {
    public:
        std::list<Object *> _objects;
        std::list<Asset *> _assets;
        Internal::Application_Internal *_applicationInternal = nullptr;
    public:
        void LoadInternal(Application *application);
        void Release();
    protected:
        virtual void LoadScene(Application *application) = 0;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_INTERNAL_H
