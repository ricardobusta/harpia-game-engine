//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_COMPONENT_H
#define HARPIAGAMEENGINE_COMPONENT_H

#include <string>
#include <list>

namespace Harpia {
    class Component {
    protected:
        virtual void Start() {};

        virtual void Update() {};
    };
} // Harpia

#endif //HARPIAGAMEENGINE_COMPONENT_H
