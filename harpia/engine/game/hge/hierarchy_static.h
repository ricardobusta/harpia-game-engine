//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_HIERARCHY_STATIC_H
#define HARPIAGAMEENGINE_HIERARCHY_STATIC_H

#include "hge/internal_defines.h"
#include <algorithm>
#include <list>
#include <memory>

namespace Harpia {

    class HierarchyStatic {
    public:
        template<class T>
        static T *AddComponent(Object *object, Internal::Application_Internal *application,
                               std::list<std::unique_ptr<Component>> &components) {
            static_assert(std::is_base_of_v<Component, T>, "Class do not extend Component");
            auto c = std::make_unique<T>();
            auto *ci = (Internal::Component_Internal *) c.get();// c style cast to override private inheritance
            InitializeInternalComponent(ci, object, application);
            auto ptr = c.get();
            components.push_back(std::move(c));
            return ptr;
        }

        template<class T>
        static T *GetComponent(std::list<std::unique_ptr<Component>> &components) {
            static_assert(std::is_base_of_v<Component, T>, "Class do not extend Component");
            auto component = std::find_if(std::begin(components), std::end(components),
                                  [&](auto &c) { return dynamic_cast<T *>(c.get()) != nullptr; });
            if (component == std::end(components)) {
                return nullptr;
            }
            return dynamic_cast<T *>(component->get());
        }

    private:
        static void InitializeInternalComponent(Internal::Component_Internal *component, Object *object,
                                                Internal::Application_Internal *application);
    };

}// namespace Harpia

#endif//HARPIAGAMEENGINE_HIERARCHY_STATIC_H
