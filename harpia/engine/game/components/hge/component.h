//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_COMPONENT_H
#define HARPIAGAMEENGINE_COMPONENT_H

#include "hge/in/component_internal.h"
#include "hge/input_reader.h"
#include "hge/object.h"
#include "hge/scene_manager.h"
#include "hge/time.h"

namespace Harpia {
    class Component : private Internal::Component_Internal {
    public:
        virtual ~Component() = default;

        [[nodiscard]] Object *GetObject() const;

        template<class T>
        T *GetComponent() const {
            return _object->GetComponent<T>();
        }

        void Start() override{
                // optional
        };

        void Update() override{
                // optional
        };

        [[nodiscard]] Object *CreateObject(std::string name) const;

        [[nodiscard]] const InputReader *Input() const;
        [[nodiscard]] const Time *Time() const;
        SceneManager *SceneManager();
        [[nodiscard]] Scene *Scene() const;

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override{
                // optional
        };
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_COMPONENT_H
