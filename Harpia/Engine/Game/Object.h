//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_OBJECT_H
#define HARPIAGAMEENGINE_OBJECT_H

#include "GlobalDefines.h"
#include <list>
#include "HierarchyStatic.h"
#include "Transform.h"

namespace Harpia {
    class Object {
    public:
        Transform transform;
    private:
        std::list<Component *> _components;
        Internal::Application_Internal *_applicationInternal;
    public:
        Object() = delete;
        explicit Object(Internal::Application_Internal *application);

        template<class T>
        T *AddComponent() {
            auto newComponent = HierarchyStatic::AddComponent<T>(this, _applicationInternal, _components);
            AddCamera(newComponent);
            AddRenderer(newComponent);
            return newComponent;
        }

        template<class T>
        T *GetComponent() {
            return HierarchyStatic::GetComponent<T>(_components);
        }

        void InternalUpdate();
    private:
        void AddCamera(Component *camera);
        void AddRenderer(Component *renderer);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_OBJECT_H
