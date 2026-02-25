//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_GUI_COMPONENT_INTERNAL_H
#define HARPIAGAMEENGINE_GUI_COMPONENT_INTERNAL_H

namespace Harpia::Internal {
    // Abstract interface implemented by all GUI components.
    // UISystem holds a list of these and calls OnGui() every frame inside
    // an ImGui NewFrame/Render pair.
    class GuiComponent_Internal {
    public:
        virtual ~GuiComponent_Internal() = default;
        virtual void OnGui() = 0;
        virtual bool IsGuiEnabledInternal() = 0;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_GUI_COMPONENT_INTERNAL_H
