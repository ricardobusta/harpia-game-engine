//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

// ImGui first — must precede any Harpia header that defines the DebugLog macro
#include "imgui/imgui.h"

#include "gui_label_component.h"

#include <cstdio>

namespace Harpia {
    GuiLabelComponent::GuiLabelComponent() {
        char buf[32];
        snprintf(buf, sizeof(buf), "##lbl_%p", static_cast<void *>(this));
        _windowId = buf;
    }

    void GuiLabelComponent::SetText(const std::string &text) {
        _text = text;
    }

    const std::string &GuiLabelComponent::GetText() const {
        return _text;
    }

    void GuiLabelComponent::SetPosition(Vector2 position) {
        _position = position;
    }

    Vector2 GuiLabelComponent::GetPosition() const {
        return _position;
    }

    void GuiLabelComponent::SetTextColor(Color color) {
        _color = color;
    }

    Color GuiLabelComponent::GetTextColor() const {
        return _color;
    }

    void GuiLabelComponent::OnGui() {
        ImGui::SetNextWindowPos(ImVec2(_position.x, _position.y), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin(_windowId.c_str(), nullptr,
                     ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoInputs |
                             ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_AlwaysAutoResize |
                             ImGuiWindowFlags_NoSavedSettings |
                             ImGuiWindowFlags_NoFocusOnAppearing |
                             ImGuiWindowFlags_NoNav);
        ImGui::TextColored(
                ImVec4(_color.r, _color.g, _color.b, _color.a),
                "%s", _text.c_str());
        ImGui::End();
    }
}// namespace Harpia
