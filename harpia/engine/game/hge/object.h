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
        std::string name = "Object";
        Transform transform;

    private:
        std::list<std::unique_ptr<Component>> _components;
        Internal::Application_Internal *_applicationInternal = nullptr;

        bool _enabled = true;
        Scene *_scene = nullptr;

    public:
        Object() = delete;
        explicit Object(std::string name, Internal::Application_Internal *application);
        ~Object();

        template<class T>
        T *AddComponent() {
            static_assert(std::is_base_of<Component, T>::value);
            auto newComponent = HierarchyStatic::AddComponent<T>(this, _applicationInternal, _components);
            if (std::is_base_of_v<RendererComponent, T>) {
                AddToRenderSystemIfRenderer((Internal::RendererComponent_Internal *) newComponent);
            }
            if (std::is_base_of_v<CameraComponent, T>) {
                AddToRenderSystemIfCamera((Internal::Camera_Internal *) newComponent);
            }
            return newComponent;
        }

        template<class T>
        T *GetComponent() {
            return HierarchyStatic::GetComponent<T>(_components);
        }

        [[nodiscard]] bool IsEnabled() const;

        void SetEnabled(bool enabled);

        void InternalUpdate() const;

        void InternalSetScene(Scene *scene);

        Scene *Scene();

    private:
        void AddToRenderSystemIfCamera(Internal::Camera_Internal *camera) const;
        void AddToRenderSystemIfRenderer(Internal::RendererComponent_Internal *renderer) const;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_OBJECT_H
