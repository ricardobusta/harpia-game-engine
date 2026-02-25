//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#include "gui_component.h"

#include "hge/in/application_internal.h"
#include "hge/object.h"
#include "hge/ui_system.h"

namespace Harpia {
    GuiComponent::~GuiComponent() {
        if (_uiSystem != nullptr) {
            _uiSystem->RemoveGuiComponent(this);
        }
    }

    void GuiComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _uiSystem = applicationInternal->_uiSystem.get();
    }

    bool GuiComponent::IsGuiEnabledInternal() {
        return GetObject()->IsEnabled();
    }
}// namespace Harpia
