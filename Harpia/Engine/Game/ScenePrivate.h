//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENEPRIVATE_H
#define HARPIAGAMEENGINE_SCENEPRIVATE_H

#include <list>
#include "GlobalDefines.h"

namespace Harpia {

    class Scene_Private {
    public:
        std::list<Object *> objects;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_SCENEPRIVATE_H
