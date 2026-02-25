//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 16/06/2022.
//

#ifndef HARPIAGAMEENGINE_UI_SYSTEM_H
#define HARPIAGAMEENGINE_UI_SYSTEM_H

#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include <list>

struct ImGuiContext;

namespace Harpia::Internal {
    class UISystem : public Internal::IApplicationSystem {
    private:
        std::list<GuiComponent_Internal *> _guiComponents;
        ImGuiContext *_imguiContext = nullptr;
        bool _initialized = false;

    public:
        int Initialize(const Configuration &configuration, RenderingSystem *renderingSystem, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;

        void AddGuiComponent(GuiComponent_Internal *component);
        void RemoveGuiComponent(GuiComponent_Internal *component);

    private:
        void RenderGui();
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_UI_SYSTEM_H
