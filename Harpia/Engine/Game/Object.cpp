//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Object.h"
#include "Component.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"
#include "Renderer_Internal.h"
#include "Camera_Internal.h"

namespace Harpia {
    Object::Object(Internal::Application_Internal *application) {
        _applicationInternal = application;
    }

    void Object::InternalUpdate() {
        for (auto c: _components) {
            auto ci = (Internal::Component_Internal *) c;
            ci->InternalUpdate();
        }
    }

    void Object::AddRenderer(Component *renderer) {
        auto r = dynamic_cast<Internal::Renderer_Internal *>(renderer);
        if (r != nullptr) {
            _applicationInternal->_renderSystem->AddRenderer(r);
        }
    }

    void Object::AddCamera(Component *camera) {
        auto c = dynamic_cast<Internal::Camera_Internal *>(camera);
        if (c != nullptr) {
            _applicationInternal->_renderSystem->AddCamera(c);
        }
    }
} // Harpia