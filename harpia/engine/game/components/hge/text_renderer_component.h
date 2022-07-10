//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H

#include "renderer_component.h"
#include <string>

namespace Harpia {
    class TextRendererComponent : public RendererComponent {
    private:
        int _charWidth = -1;
        int _charHeight = -1;
        std::string _text = {};
        MeshAsset *_textMesh = nullptr;

        Internal::RenderingSystem *_renderingSystem;

    public:
        void SetText(const std::string &text);
        void SetFontMaterial(MaterialAsset *material, int charWidth, int charHeight);

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override;
    private:
        void CreateMesh();
        void UpdateMesh();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
