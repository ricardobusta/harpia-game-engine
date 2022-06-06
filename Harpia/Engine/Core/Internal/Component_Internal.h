//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_COMPONENT_INTERNAL_H
#define HARPIAGAMEENGINE_COMPONENT_INTERNAL_H

#include "GlobalDefines.h"
#include "InternalDefines.h"

namespace Harpia {
    class Component_Internal {
    public:
        Object *_object = nullptr;
        Application_Internal *_application = nullptr;
    private:
        bool started = false;
    public:
        void Initialize(Object *object, Application_Internal *applicationInternal);

        void InternalUpdate();

    protected:
        virtual void Initialize_Internal(Application_Internal *applicationInternal) = 0;

        virtual void Start() = 0;

        virtual void Update() = 0;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_COMPONENT_INTERNAL_H
