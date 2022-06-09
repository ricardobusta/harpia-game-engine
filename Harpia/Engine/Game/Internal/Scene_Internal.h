//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_INTERNAL_H
#define HARPIAGAMEENGINE_SCENE_INTERNAL_H

#include <list>
#include "GlobalDefines.h"

namespace Harpia::Internal {

    class Scene_Internal {
    public:
        std::list<Object *> _objects;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_INTERNAL_H
