//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_INTERNAL_H
#define HARPIAGAMEENGINE_SCENE_INTERNAL_H

#include "hge/internal_defines.h"
#include <list>

namespace Harpia::Internal {
    class Scene_Internal {
    public:
        std::list<Object *> _objects;
        std::list<Asset *> _assets;
        Internal::Application_Internal *_applicationInternal = nullptr;
        bool _loaded;

        void LoadInternal(Application *application);
        virtual ~Scene_Internal() = default;
        virtual void Release() = 0;

    protected:
        virtual void LoadScene(Application *application) = 0;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_SCENE_INTERNAL_H
