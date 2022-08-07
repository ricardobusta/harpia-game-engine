//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "main_scene.h"
#include "main_scene/main_scene_controller.h"
#include <hge/application.h>
#include <hge/camera_component.h>
#include <hge/color.h>
#include <hge/debug.h>
#include <hge/material_asset.h>
#include <hge/text_renderer_component.h>
#include <hge/texture_asset.h>

using namespace Harpia;

namespace SampleGame {
    void MainScene::CreateText(const std::string &text, const Vector2 &pos, MaterialAsset *material) {
        auto textObject = CreateObject("Text");
        auto textRenderer = textObject->AddComponent<TextRendererComponent>();
        textObject->transform.SetPosition(pos);
        textRenderer->SetFontMaterial(material, 7, 9);
        textRenderer->SetText(text);
    }

    void MainScene::Load(Harpia::Application *application) {
        DebugLog("Starting MainScene");

        auto sizeV = 20.0f;

        auto cameraObject = CreateObject("Camera");
        auto camera = cameraObject->AddComponent<CameraComponent>();
        auto sizeH = sizeV * application->GetScreenAspect();
        camera->SetOrthographic(sizeV, 1, -1);
        camera->SetViewport(RectF{0, 0, 1, 1});

        auto fontAtlas = LoadTextureAsset("assets/fonts/pixel.png");
        fontAtlas->_filter = TextureFilter::Nearest;
        auto fontShader = LoadShaderAsset("assets/shaders/text.vert", "assets/shaders/text.frag");
        auto fontMaterial = LoadMaterialAsset(fontShader);
        fontMaterial->SetTexture(fontAtlas);
        fontMaterial->SetColor(Color::white);
        fontMaterial->_transparent = true;

        auto controllerObject = CreateObject("SceneController");
        controllerObject->AddComponent<MainSceneController>();

        auto space = 1.8f;
        auto tab = 1.0f;
        auto v = sizeV;
        auto h = -sizeH + tab;

        CreateText("Press Key to Load Scene", {h, v -= space}, fontMaterial);
        CreateText("[1] All The Things", {h += tab, v -= 4}, fontMaterial);
        CreateText("[2] Spaceships", {h, v -= space}, fontMaterial);
        CreateText("[3] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[4] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[5] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[6] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[7] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[8] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[9] ... soon ...", {h, v -= space}, fontMaterial);
        CreateText("[Esc] Quit", {h, v -= space}, fontMaterial);
    }
}// namespace SampleGame