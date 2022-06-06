//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_OBJECT_H
#define HARPIAGAMEENGINE_OBJECT_H

#include "GlobalDefines.h"
#include <list>
#include <type_traits>

namespace Harpia {

    class Object {
    private:
        std::list<Component *> _components;
    public:
        bool flaggedToBeDestroyed = false;

        template<class T>
        void AddComponent() {
            static_assert(std::is_base_of<Component, T>::value, "Class do not extend Component");
            Component *c = new T(this);
            AddComponent(c);
        }

    private:
        void AddComponent(Component *component);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_OBJECT_H
