//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/object.h"

#include <utility>
#include "hge/camera_component.h"
#include "hge/camera_internal.h"
#include "hge/component.h"
#include "hge/in/application_internal.h"
#include "hge/renderer_component_internal.h"
#include "hge/rendering_system.h"

namespace Harpia {
    Object::Object(std::string name, Internal::Application_Internal *application)
        : name(std::move(name)), _applicationInternal(application) {
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

    void Object::AddToRenderSystemIfRenderer(Internal::RendererComponent_Internal *renderer) {
        if (renderer != nullptr) {
            _applicationInternal->_renderSystem->AddRenderer(renderer);
        }
    }
}// namespace Harpia