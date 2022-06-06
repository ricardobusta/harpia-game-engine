//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_H
#define HARPIAGAMEENGINE_SCENE_H

#include "Internal/Scene_Internal.h"
#include "Internal/InternalDefines.h"

namespace Harpia {
    class Scene : private Scene_Internal {
    private:
        Application_Internal *_applicationInternal = nullptr;
    public:
        void Load(Application *application);

        void Unload();

    protected:
        virtual void Load() = 0;

        Object *CreateObject();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_H
