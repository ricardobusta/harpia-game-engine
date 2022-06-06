//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_COMPONENT_H
#define HARPIAGAMEENGINE_COMPONENT_H

#include <string>
#include <list>
#include "Internal/Component_Internal.h"
#include "Object.h"

namespace Harpia {
    class Component : private Component_Internal {
    private:

    public:
        Object *GetObject();

        template<class T>
        T *GetComponent() {
            return _object->template GetComponent<T>();
        }

    protected:
        virtual void Start() {};

        virtual void Update() {};
    };
} // Harpia

#endif //HARPIAGAMEENGINE_COMPONENT_H
