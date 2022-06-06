//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_COMPONENT_INTERNAL_H
#define HARPIAGAMEENGINE_COMPONENT_INTERNAL_H

#include "GlobalDefines.h"
#include "InternalDefines.h"

namespace Harpia {
    class Component_Internal {
    public:
        Object * _object = nullptr;

        void Initialize(Object * object, Application_Internal * applicationInternal);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_COMPONENT_INTERNAL_H
