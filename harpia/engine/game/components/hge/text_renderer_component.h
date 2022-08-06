//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H

#include "renderer_component.h"
#include <string>

namespace Harpia {
    class TextRendererComponent : public RendererComponent {
    public:
        const static std::string ASCII_TABLE;
    private:
        int _charWidth = -1;
        int _charHeight = -1;
        std::string _text = {};
        std::string _table = {};
        MeshAsset *_textMesh = nullptr;
        Vector2 _size;

    public:
        void SetText(const std::string &text);
        void SetFontMaterial(MaterialAsset *material, int charWidth, int charHeight, const std::string &table = ASCII_TABLE);
        [[nodiscard]] Vector2 GetSize() const;

    private:
        void UpdateMesh();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
