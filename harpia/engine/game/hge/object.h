//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_OBJECT_H
#define HARPIAGAMEENGINE_OBJECT_H

#include "hge/debug.h"
#include "hge/global_defines.h"
#include "hge/hierarchy_static.h"
#include "hge/transform.h"
#include <list>

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
            if (std::is_base_of<RendererComponent, T>::value) {
                AddToRenderSystemIfRenderer((Internal::RendererComponent_Internal *) newComponent);
            }
            if (std::is_base_of<CameraComponent, T>::value) {
                AddToRenderSystemIfCamera((Internal::Camera_Internal *) newComponent);
            }
            return newComponent;
        }

        template<class T>
        T *GetComponent() {
            return HierarchyStatic::GetComponent<T>(_components);
        }

        void InternalUpdate();

    private:
        void AddToRenderSystemIfCamera(Internal::Camera_Internal *camera);
        void AddToRenderSystemIfRenderer(Internal::RendererComponent_Internal *renderer);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_OBJECT_H
