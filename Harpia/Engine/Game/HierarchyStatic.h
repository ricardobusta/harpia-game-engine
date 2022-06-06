//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_HIERARCHYSTATIC_H
#define HARPIAGAMEENGINE_HIERARCHYSTATIC_H

#include "Internal/InternalDefines.h"
#include <algorithm>
#include <list>
#include "Debug.h"

namespace Harpia {

    class HierarchyStatic {
    public:
        template<class T>
        static T *AddComponent(Object *object, Application_Internal *application, std::list<Component *> &components) {
            static_assert(std::is_base_of<Component, T>::value, "Class do not extend Component");
            auto *c = new T();
            auto *ci = (Component_Internal *) c; // c style cast to override private inheritance
            InitializeInternalComponent(ci, object, application);
            components.push_back(c);
            return c;
        }

        template<class T>
        static T *GetComponent(std::list<Component *> &components) {
            static_assert(std::is_base_of<Component, T>::value, "Class do not extend Component");
            auto c = std::find_if(std::begin(components), std::end(components),
                                  [&](auto c) { return dynamic_cast<T *>(c) != nullptr; });
            if (c == std::end(components)) {
                return nullptr;
            }
            return dynamic_cast<T *>(*c);
        }

    private:
        static void InitializeInternalComponent(Component_Internal *component, Object *object,
                                                Application_Internal *application);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_HIERARCHYSTATIC_H
