//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/Object.h"
#include "hge/Component.h"
#include "hge/in/Application_Internal.h"
#include "hge/RenderingSystem.h"
#include "hge/Renderer_Internal.h"
#include "hge/Camera_Internal.h"
#include "hge/CameraComponent.h"

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

    void Object::AddToRenderSystemIfCamera(Internal::Camera_Internal *camera) {
        if (camera != nullptr) {
            _applicationInternal->_renderSystem->AddCamera(camera);
        }
    }

    void Object::AddToRenderSystemIfRenderer(Internal::Renderer_Internal *renderer) {
        if (renderer != nullptr) {
            _applicationInternal->_renderSystem->AddRenderer(renderer);
        }
    }
} // Harpia