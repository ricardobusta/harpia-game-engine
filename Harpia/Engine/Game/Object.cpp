//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Object.h"
#include "Component.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"
#include "Renderer_Internal.h"
#include "Camera_Internal.h"
#include "Debug.h"
#include "CameraComponent.h"

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

    void Object::AddToRenderSystemIfCamera(CameraComponent *camera) {
        if (camera != nullptr) {
            _applicationInternal->_renderSystem->AddCamera((Internal::Camera_Internal *) camera);
        }
    }

    void Object::AddToRenderSystemIfRenderer(RendererComponent *renderer) {
        if (renderer != nullptr) {
            _applicationInternal->_renderSystem->AddRenderer((Internal::Renderer_Internal *) renderer);
        }
    }
} // Harpia