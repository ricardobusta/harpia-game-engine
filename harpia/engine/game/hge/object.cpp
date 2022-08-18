//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/object.h"

#include "hge/camera_component.h"
#include "hge/camera_internal.h"
#include "hge/component.h"
#include "hge/in/application_internal.h"
#include "hge/renderer_component_internal.h"
#include "hge/rendering_system.h"
#include <utility>

namespace Harpia {
    Object::Object(std::string name, Internal::Application_Internal *application)
        : name(std::move(name)), _applicationInternal(application) {
    }

    Object::~Object() {
        DebugLog("Destroying %s object.", name.c_str());
        _components.clear();
    }

    void Object::InternalUpdate() const {
        for (auto const &c: _components) {
            auto ci = (Internal::Component_Internal *) c.get();
            ci->InternalUpdate();
        }
    }

    void Object::AddToRenderSystemIfCamera(Internal::Camera_Internal *camera) const {
        if (camera != nullptr) {
            _applicationInternal->_renderSystem->AddCamera(camera);
        }
    }

    void Object::AddToRenderSystemIfRenderer(Internal::RendererComponent_Internal *renderer) const {
        if (renderer != nullptr) {
            _applicationInternal->_renderSystem->AddRenderer(renderer);
        }
    }
}// namespace Harpia