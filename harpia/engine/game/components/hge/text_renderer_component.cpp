//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#include "text_renderer_component.h"
#include "hge/in/application_internal.h"
#include "hge/rendering_system.h"

namespace Harpia {
    void TextRendererComponent::SetText(const std::string &text) {
        _text = text;

        UpdateMesh();
    }

    void TextRendererComponent::SetFontMaterial(MaterialAsset *material, const int charWidth, const int charHeight) {
        SetMaterial(material);
        if (charWidth != _charWidth || charHeight != _charHeight) {
            _charWidth = charWidth;
            _charHeight = charHeight;
            UpdateMesh();
        }
    }

    void TextRendererComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _renderingSystem = applicationInternal->_renderSystem;
    }

    void GenerateCharacterMesh(int index, std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indexes) {
        unsigned int nextIndex = index * 4;
        DebugLog("Next index: %d", nextIndex);
        auto pos = (float) index;
        
        positions.insert(positions.end(), {
                                                  pos + 0, 0, 0,//
                                                  pos + 1, 0, 0,//
                                                  pos + 1, 1, 0,//
                                                  pos + 0, 1, 0 //
                                          });

        normals.insert(normals.end(), {
                                              0, 0, 1,//
                                              0, 0, 1,//
                                              0, 0, 1,//
                                              0, 0, 1 //
                                      });

        uvs.insert(uvs.end(),
                   {
                           0, 0,//
                           1, 0,//
                           1, 1,//
                           0, 1 //
                   });

        indexes.insert(indexes.end(), {nextIndex + 0, nextIndex + 1, nextIndex + 2,//
                                       nextIndex + 0, nextIndex + 2, nextIndex + 3});
    }

    void GenerateTextMesh(const std::string &text, std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indexes) {
        auto vertexCount = 3 * 2 * text.length();
        positions.clear();
        positions.reserve(3 * vertexCount);
        normals.clear();
        normals.reserve(3 * vertexCount);
        uvs.clear();
        uvs.reserve(2 * vertexCount);
        indexes.clear();
        indexes.reserve(vertexCount);

        for (auto i = 0; i < text.length(); i++) {
            GenerateCharacterMesh(i, positions, normals, uvs, indexes);
            DebugLog("Generating mesh for character %c", text[i]);
        }
    }


    void TextRendererComponent::UpdateMesh() {
        if (_charWidth < 0 || _charHeight < 0) {
            return;
        }

        std::vector<float> positions, normals, uvs;
        std::vector<unsigned int> indexes;

        GenerateTextMesh(_text, positions, normals, uvs, indexes);

        if (_textMesh == nullptr) {
            _textMesh = _renderingSystem->LoadMesh(positions, normals, uvs, indexes);
            SetMesh(_textMesh);
        } else {
            _renderingSystem->UpdateMesh(_textMesh, positions, normals, uvs, indexes);
        }
    }
}// namespace Harpia