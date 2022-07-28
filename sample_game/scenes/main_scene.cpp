//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "main_scene.h"
#include <hge/application.h>
#include <hge/camera_component.h>
#include <hge/color.h>
#include <hge/debug.h>
#include <hge/material_asset.h>
#include <hge/text_renderer_component.h>
#include <hge/texture_asset.h>

using namespace Harpia;

namespace SampleGame {
    void MainScene::CreateText(const std::string &text, const Vector3 &pos, MaterialAsset *material) {
        auto textObject = CreateObject("Text");
        auto textRenderer = textObject->AddComponent<TextRendererComponent>();
        textObject->transform.SetPosition(pos);
        textRenderer->SetFontMaterial(material, 7, 9);
        textRenderer->SetText(text);
    }

    void MainScene::Load(Harpia::Application *application) {
        DebugLog("Starting MainScene");

        auto sizeV = 10.0f;

        auto cameraObject = CreateObject("Camera");
        cameraObject->transform.SetPosition({0, 0, 15.0f});
        //cameraObject->transform.Rotate(-15 * Math::Deg2Rad, {00, 0, 0});
        auto screenSize = application->screenSize;
        auto viewport = RectInt{0, 0, screenSize.x, screenSize.y};
        auto camera = cameraObject->AddComponent<CameraComponent>();
        auto aspect = (float) viewport.w / (float) viewport.h;
        auto sizeH = sizeV * aspect;
        camera->SetOrthographic(sizeV, aspect, 60, -60);
        camera->SetViewport(viewport);
        camera->SetClearColor(Color(0.3f, 0.3f, 0.3f, 0.0f));

        auto fontAtlas = LoadTextureAsset("assets/fonts/pixel.png");
        fontAtlas->_filter = TextureFilter::Nearest;
        auto fontShader = LoadShaderAsset("assets/shaders/text.vert", "assets/shaders/text.frag");
        auto fontMaterial = LoadMaterialAsset(fontShader);
        fontMaterial->SetTexture(fontAtlas);
        fontMaterial->SetColor(Color::white);
        fontMaterial->_transparent = true;

        CreateText("Press Key to Load Scene", {-sizeH, sizeV - 1.5f, 0}, fontMaterial);
        CreateText("[1] All The Things", {-sizeH, sizeV - 5.0f, 0}, fontMaterial);
        CreateText("...", {-sizeH, sizeV - 6.5f, 0}, fontMaterial);
    }
}// namespace SampleGame