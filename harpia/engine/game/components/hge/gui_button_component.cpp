//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

// ImGui first — must precede any Harpia header that defines the DebugLog macro
#include "imgui/imgui.h"

#include "gui_button_component.h"
#include <cstdio>

namespace Harpia {
    GuiButtonComponent::GuiButtonComponent() {
        char buf[32];
        snprintf(buf, sizeof(buf), "##btn_%p", static_cast<void *>(this));
        _windowId = buf;
    }

    void GuiButtonComponent::SetLabel(const std::string &label) {
        _label = label;
    }

    const std::string &GuiButtonComponent::GetLabel() const {
        return _label;
    }

    void GuiButtonComponent::SetPosition(Vector2 position) {
        _position = position;
    }

    Vector2 GuiButtonComponent::GetPosition() const {
        return _position;
    }

    void GuiButtonComponent::SetSize(Vector2 size) {
        _size = size;
    }

    Vector2 GuiButtonComponent::GetSize() const {
        return _size;
    }

    bool GuiButtonComponent::WasClicked() const {
        return _wasClicked;
    }

    void GuiButtonComponent::OnGui() {
        _wasClicked = false;

        ImGui::SetNextWindowPos(ImVec2(_position.x, _position.y), ImGuiCond_Always);
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::Begin(_windowId.c_str(), nullptr,
                     ImGuiWindowFlags_NoDecoration |
                             ImGuiWindowFlags_NoMove |
                             ImGuiWindowFlags_AlwaysAutoResize |
                             ImGuiWindowFlags_NoSavedSettings |
                             ImGuiWindowFlags_NoFocusOnAppearing |
                             ImGuiWindowFlags_NoNav);

        const bool clicked = ImGui::Button(
                _label.c_str(),
                (_size.x > 0 && _size.y > 0) ? ImVec2(_size.x, _size.y) : ImVec2(0, 0));

        if (clicked) {
            _wasClicked = true;
            onClick.Invoke();
        }

        ImGui::End();
    }
}// namespace Harpia
