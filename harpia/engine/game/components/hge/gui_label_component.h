//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_GUI_LABEL_COMPONENT_H
#define HARPIAGAMEENGINE_GUI_LABEL_COMPONENT_H

#include "gui_component.h"
#include "hge/color.h"
#include "hge/harpia_math.h"
#include <string>

namespace Harpia {
    // Renders a text label overlay using ImGui::Text.
    // Position is in screen-space pixels; the window auto-sizes to the text.
    class GuiLabelComponent : public GuiComponent {
    private:
        std::string _text;
        Vector2 _position = {0, 0};
        Color _color = Color(1, 1, 1, 1);
        std::string _windowId;

    public:
        GuiLabelComponent();

        void SetText(const std::string &text);
        [[nodiscard]] const std::string &GetText() const;

        void SetPosition(Vector2 position);
        [[nodiscard]] Vector2 GetPosition() const;

        void SetTextColor(Color color);
        [[nodiscard]] Color GetTextColor() const;

    private:
        void OnGui() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_GUI_LABEL_COMPONENT_H
