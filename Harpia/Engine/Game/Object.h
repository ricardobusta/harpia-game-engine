//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_OBJECT_H
#define HARPIAGAMEENGINE_OBJECT_H

#include "GlobalDefines.h"
#include <list>
#include "HierarchyStatic.h"

namespace Harpia {
    class Object {
    private:
        std::list<Component *> _components;
        Application_Internal *_applicationInternal;
    public:
        Object() = delete;
        explicit Object(Application_Internal * application);

        template<class T>
        T* AddComponent() {
            return HierarchyStatic::AddComponent<T>(this, _applicationInternal, _components);
        }

        template<class T>
        T *GetComponent() {
            return HierarchyStatic::GetComponent<T>(_components);
        }

        void Update();
    private:
    };
} // Harpia

#endif //HARPIAGAMEENGINE_OBJECT_H
