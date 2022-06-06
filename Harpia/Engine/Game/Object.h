//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_OBJECT_H
#define HARPIAGAMEENGINE_OBJECT_H

#include "GlobalDefines.h"
#include <list>
#include <type_traits>
#include <algorithm>
#include "Internal/Component_Internal.h"

namespace Harpia {
    class Object {
    private:
        std::list<Component *> _components;
        Application_Internal *_applicationInternal;
    public:
        template<class T>
        void AddComponent() {
            static_assert(std::is_base_of<Component, T>::value, "Class do not extend Component");
            auto *c = new T();
            auto *ci = (Component_Internal *) c; // c style cast to override private inheritance
            ci->Initialize(this, _applicationInternal);
            _components.push_back(c);
        }

        template<class T>
        T *GetComponent() {
            static_assert(std::is_base_of<Component, T>::value, "Class do not extend Component");
            auto c = std::find_if(std::begin(_components), std::end(_components),
                                  [&](auto c) { return typeid(c) == typeid(T); });
            if (c == std::end(_components)) {
                return nullptr;
            }
            return dynamic_cast<T *>(*c);
        }

    private:
    };
} // Harpia

#endif //HARPIAGAMEENGINE_OBJECT_H
