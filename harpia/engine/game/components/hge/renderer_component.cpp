//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#include "renderer_component.h"

#include "hge/in/application_internal.h"
#include "hge/renderer_component_platform.h"
#include "hge/rendering_system.h"

namespace Harpia {
    RendererComponent::RendererComponent()
        : Component(), Internal::RendererComponent_Internal() {
    }

    RendererComponent::~RendererComponent() {
        _renderingSystem->RemoveRenderer(this);
    }

    void RendererComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _renderingSystem = applicationInternal->_renderSystem;
    }

    void RendererComponent::SetMesh(MeshAsset *mesh) {
        if (mesh == nullptr) {
            DebugLogError("Mesh was null");
            return;
        }
        _platform->SetMesh(mesh);
    }

    void RendererComponent::SetMaterial(MaterialAsset *material) {
        _platform->SetMaterial(material);
    }

    const MaterialAsset *RendererComponent::GetMaterial() const {
        return _platform->GetMaterial();
    }

    Transform *RendererComponent::GetTransformInternal() {
        return &GetObject()->transform;
    }
}// namespace Harpia