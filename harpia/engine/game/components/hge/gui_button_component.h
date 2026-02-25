//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_GUI_BUTTON_COMPONENT_H
#define HARPIAGAMEENGINE_GUI_BUTTON_COMPONENT_H

#include "gui_component.h"
#include "hge/event.h"
#include "hge/harpia_math.h"
#include <string>

namespace Harpia {
    class GuiButtonComponent : public GuiComponent {
    private:
        std::string _label;
        Vector2 _position = {0, 0};
        Vector2 _size = {0, 0};
        bool _wasClicked = false;
        std::string _windowId;

    public:
        Event<> onClick;

    public:
        GuiButtonComponent();

        void SetLabel(const std::string &label);
        [[nodiscard]] const std::string &GetLabel() const;

        void SetPosition(Vector2 position);
        [[nodiscard]] Vector2 GetPosition() const;

        // Set explicit button size. Pass {0, 0} to auto-size from the label text.
        void SetSize(Vector2 size);
        [[nodiscard]] Vector2 GetSize() const;

        // Returns true if the button was clicked during the current frame.
        // Resets automatically at the start of the next OnGui call.
        [[nodiscard]] bool WasClicked() const;

    private:
        void OnGui() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_GUI_BUTTON_COMPONENT_H
