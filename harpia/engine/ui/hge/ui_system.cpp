//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 16/06/2022.
//

// ImGui headers MUST come first — before any Harpia header that defines the
// DebugLog macro. If DebugLog is already defined as a macro when imgui.h is
// parsed, the preprocessor would mangle ImGui's own ImGui::DebugLog API.
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_sdl3.h"

// Harpia headers after ImGui — DebugLog macro is now safe to define
#include "ui_system.h"

#include "gui_component_internal.h"
#include "hge/configuration.h"
#include "hge/core_system.h"
#include "hge/debug.h"
#include "hge/rendering_system.h"

#include <SDL3/SDL.h>

namespace Harpia::Internal {
    int UISystem::Initialize(const Configuration &configuration, RenderingSystem *renderingSystem, CoreSystem *coreSystem) {
        auto window = coreSystem->GetWindow();
        if (window == nullptr) {
            HDebugLogError("UISystem: window is null, cannot initialize ImGui.");
            return -1;
        }

        // The GL context was already created by RenderingSystemGL — retrieve it from SDL.
        auto glContext = SDL_GL_GetCurrentContext();
        if (glContext == nullptr) {
            HDebugLogError("UISystem: no current GL context found. RenderingSystem must be initialized first.");
            return -1;
        }

        HDebugLog("UISystem: calling IMGUI_CHECKVERSION");
        IMGUI_CHECKVERSION();
        HDebugLog("UISystem: calling ImGui::CreateContext");
        _imguiContext = ImGui::CreateContext();
        ImGui::SetCurrentContext(_imguiContext);
        HDebugLog("UISystem: configuring ImGuiIO");
        ImGuiIO &io = ImGui::GetIO();
        io.IniFilename = nullptr;// Disable imgui.ini persistence

        HDebugLog("UISystem: calling ImGui::StyleColorsDark");
        ImGui::StyleColorsDark();

        HDebugLog("UISystem: calling ImGui_ImplSDL3_InitForOpenGL");
        if (!ImGui_ImplSDL3_InitForOpenGL(window, glContext)) {
            HDebugLogError("UISystem: ImGui_ImplSDL3_InitForOpenGL failed.");
            return -1;
        }
        // Pass nullptr so ImGui auto-selects the correct GLSL version for the platform:
        //   macOS  → "#version 150"  (Core Profile minimum)
        //   other  → "#version 130"
        //   ES3    → "#version 300 es"  (via IMGUI_IMPL_OPENGL_ES3)
        HDebugLog("UISystem: calling ImGui_ImplOpenGL3_Init");
        if (!ImGui_ImplOpenGL3_Init(nullptr)) {
            HDebugLogError("UISystem: ImGui_ImplOpenGL3_Init failed.");
            return -1;
        }
        HDebugLog("UISystem: ImGui_ImplOpenGL3_Init succeeded");

        // Forward every SDL event to ImGui before the engine processes it.
        coreSystem->onSDLEvent += [](const SDL_Event &e) {
            ImGui_ImplSDL3_ProcessEvent(&e);
        };

        // Render ImGui overlay after all cameras draw but before the buffer swap.
        renderingSystem->onPreSwapBuffer += [this]() {
            RenderGui();
        };

        _initialized = true;
        HDebugLog("UISystem: ImGui initialized.");
        return 0;
    }

    int UISystem::GetInitFlags() {
        return 0;
    }

    int UISystem::GetWindowFlags() {
        return 0;
    }

    void UISystem::Quit() {
        if (!_initialized) return;
        ImGui::SetCurrentContext(_imguiContext);
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
        _imguiContext = nullptr;
        _initialized = false;
        HDebugLog("UISystem: ImGui shut down.");
    }

    void UISystem::AddGuiComponent(GuiComponent_Internal *component) {
        _guiComponents.push_back(component);
    }

    void UISystem::RemoveGuiComponent(GuiComponent_Internal *component) {
        _guiComponents.remove(component);
    }

    void UISystem::RenderGui() {
        ImGui::SetCurrentContext(_imguiContext);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        for (auto *component: _guiComponents) {
            if (component->IsGuiEnabledInternal()) {
                component->OnGui();
            }
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}// namespace Harpia::Internal
