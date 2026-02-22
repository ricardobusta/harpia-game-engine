//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
#define HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H

#include "renderer_component.h"
#include <array>
#include <string>
#include <vector>

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
        void SetText(const std::string_view &text);
        void SetFontMaterial(MaterialAsset *material, int charWidth, int charHeight, const std::string_view &table = ASCII_TABLE);
        [[nodiscard]] Vector2 GetSize() const;

    private:
        void UpdateMesh();
        void GenerateCharacterMesh(int index, float charAspect, const std::array<float, 4> &uv,
                                   std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs,
                                   std::vector<unsigned int> &indexes) const;
        void GenerateTextMesh(const std::string &text, const std::string_view &table, float charAspect, float uvX,
                              float uvY, int rowSize, std::vector<float> &positions, std::vector<float> &normals,
                              std::vector<float> &uvs, std::vector<unsigned int> &indexes);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TEXT_RENDERER_COMPONENT_H
