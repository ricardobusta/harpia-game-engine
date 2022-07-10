//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/07/2022.
//

#include "text_renderer_component.h"
#include "hge/in/application_internal.h"
#include "hge/mesh_generator.h"
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

    void GenerateMesh(std::vector<float> &positions, std::vector<float> &normals, std::vector<float> &uvs, std::vector<unsigned int> &indexes) {
        positions = {
                0, 0, 0,//
                10, 0, 0,//
                10, 10, 0,//
                0, 10, 0 //
        };
        normals = {
                0, 0, 1,//
                0, 0, 1,//
                0, 0, 1,//
                0, 0, 1,//
        };
        uvs = {
                0, 0,//
                1, 0,//
                1, 1,//
                0, 1,//
        };
        indexes = {
                0, 1, 2,//
                0, 2, 3 //
        };
    }

    void TextRendererComponent::UpdateMesh() {
        if (_charWidth < 0 || _charHeight < 0) {
            return;
        }

        std::vector<float> positions, normals, uvs;
        std::vector<unsigned int> indexes;

        GenerateMesh(positions, normals, uvs, indexes);

        if (_textMesh == nullptr) {
            _textMesh = _renderingSystem->LoadMesh(positions, normals, uvs, indexes);
            SetMesh(_textMesh);
        } else {
            _renderingSystem->UpdateMesh(_textMesh, positions, normals, uvs, indexes);
        }
    }
}// namespace Harpia