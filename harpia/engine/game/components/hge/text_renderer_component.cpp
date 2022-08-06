//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#include "text_renderer_component.h"
#include "hge/in/application_internal.h"
#include "hge/material_asset.h"
#include "hge/rendering_system.h"
#include "hge/texture_asset.h"
#include <cmath>

namespace Harpia {
    const std::string TextRendererComponent::ASCII_TABLE = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";// NOLINT(cert-err58-cpp)

    void TextRendererComponent::SetText(const std::string &text) {
        _text = text;
        UpdateMesh();
    }

    void TextRendererComponent::SetFontMaterial(MaterialAsset *material, const int charWidth, const int charHeight, const std::string &table) {
        SetMaterial(material);
        if (charWidth != _charWidth || charHeight != _charHeight || table != _table) {
            _charWidth = charWidth;
            _charHeight = charHeight;
            _table = table;
            UpdateMesh();
        }
    }

    void TextRendererComponent::GenerateCharacterMesh(const int index, const float charAspect, const std::array<float, 4> &uv, std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indexes) {
        unsigned int nextIndex = index * 4;
        auto xOffset = (float) index * charAspect;

        positions.insert(positions.end(), {
                                                  xOffset + 0, 0, 0,         //
                                                  xOffset + charAspect, 0, 0,//
                                                  xOffset + charAspect, 1, 0,//
                                                  xOffset + 0, 1, 0          //
                                          });

        normals.insert(normals.end(), {
                                              0, 0, 1,//
                                              0, 0, 1,//
                                              0, 0, 1,//
                                              0, 0, 1 //
                                      });

        uvs.insert(uvs.end(),
                   {
                           uv[0], uv[2],//
                           uv[1], uv[2],//
                           uv[1], uv[3],//
                           uv[0], uv[3] //
                   });

        indexes.insert(indexes.end(), {nextIndex + 0, nextIndex + 1, nextIndex + 2,//
                                       nextIndex + 0, nextIndex + 2, nextIndex + 3});
    }

    void TextRendererComponent::GenerateTextMesh(const std::string &text, const std::string &table, const float charAspect, const float uvX, const float uvY, const int rowSize, std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indexes) {
        auto vertexCount = 3 * 2 * text.length();
        positions.clear();
        positions.reserve(3 * vertexCount);
        normals.clear();
        normals.reserve(3 * vertexCount);
        uvs.clear();
        uvs.reserve(2 * vertexCount);
        indexes.clear();
        indexes.reserve(vertexCount);

        _size = {
                std::min((float) text.length(), (float) rowSize) * charAspect,
                text.length() > 0 ? std::ceil((float) text.length() / (float) rowSize) : 0};

        for (auto i = 0; i < text.length(); i++) {
            auto charIdx = table.find_first_of(text[i]);
            if (charIdx == std::string::npos) {
                continue;
            }
            auto x = (float) (charIdx % rowSize);
            auto y = (float) (charIdx / rowSize);// NOLINT(bugprone-integer-division)

            GenerateCharacterMesh(i, charAspect, {x * uvX, (x + 1.0f) * uvX, (y + 1.0f) * uvY, y * uvY}, positions, normals, uvs, indexes);
        }
    }


    void TextRendererComponent::UpdateMesh() {
        if (_charWidth < 0 || _charHeight < 0) {
            return;
        }
        auto mat = GetMaterial();
        if (mat == nullptr) {
            return;
        }
        auto tex = mat->GetTexture();
        if (tex == nullptr) {
            return;
        }

        std::vector<float> positions, normals, uvs;
        std::vector<unsigned int> indexes;

        auto uvOffsetX = (float) _charWidth / (float) tex->_width;
        auto uvOffsetY = (float) _charHeight / (float) tex->_height;
        auto charAspect = (float) _charWidth / (float) _charHeight;
        auto rowCount = (int) std::floor((float) tex->_width / (float) _charWidth);

        GenerateTextMesh(_text, _table, charAspect, uvOffsetX, uvOffsetY, rowCount, positions, normals, uvs, indexes);

        if (_textMesh == nullptr) {
            _textMesh = _renderingSystem->LoadMesh(positions, normals, uvs, indexes);
            SetMesh(_textMesh);
        } else {
            _renderingSystem->UpdateMesh(_textMesh, positions, normals, uvs, indexes);
        }
    }

    Vector2 TextRendererComponent::GetSize() const {
        return _size;
    }
}// namespace Harpia