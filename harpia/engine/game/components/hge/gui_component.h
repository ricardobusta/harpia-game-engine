//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_GUI_COMPONENT_H
#define HARPIAGAMEENGINE_GUI_COMPONENT_H

#include "hge/component.h"
#include "hge/gui_component_internal.h"

namespace Harpia {
    // Base class for all ImGui-based overlay components.
    // Subclasses implement OnGui() and call ImGui widget functions there.
    // Position is in screen-space pixels (top-left origin, matching ImGui convention).
    class GuiComponent : public Component, public Internal::GuiComponent_Internal {
    protected:
        Internal::UISystem *_uiSystem = nullptr;

    public:
        GuiComponent() = default;
        ~GuiComponent() override;

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override;

    private:
        bool IsGuiEnabledInternal() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_GUI_COMPONENT_H
