//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 28/07/2022.
//

#include "all_the_things_scene.h"

#include "character_controller.h"
#include "rotate_around.h"
#include "test_audio.h"
#include <hge/application.h>
#include <hge/audio_component.h>
#include <hge/camera_component.h>
#include <hge/color.h>
#include <hge/debug.h>
#include <hge/material_asset.h>
#include <hge/music_component.h>
#include <hge/renderer_component.h>
#include <hge/text_renderer_component.h>
#include <hge/texture_asset.h>

using namespace Harpia;

namespace SampleGame {
    static int shapeCount = 0;

    Harpia::Object *AllTheThingsScene::CreateRotatingShape(const Vector3 &position, const Vector3 &rotatingSpeed, const Vector3 &scale,
                                                           const Color &color, ShaderAsset *shader, TextureAsset *texture, MeshAsset *mesh) {
        auto shape = CreateObject("Shape_" + std::to_string(shapeCount++));
        auto rotateScript = shape->AddComponent<RotateAround>();
        rotateScript->target = &shape->transform;
        rotateScript->speed = rotatingSpeed;
        shape->transform.SetPosition(position);
        shape->transform.SetScale(scale);
        auto rend = shape->AddComponent<RendererComponent>();
        auto mat = LoadMaterialAsset(shader);
        mat->SetTexture(texture);
        mat->SetColor(color);
        rend->SetMaterial(mat);
        rend->SetMesh(mesh);
        return shape;
    }

    void AllTheThingsScene::Load(Harpia::Application *application) {
        DebugLog("Starting AllTheThingsScene");

        CreateAudioObjects();

        auto defaultShader = LoadShaderAsset("assets/shaders/default.vert", "assets/shaders/default.frag");
        auto tileTexture = LoadTextureAsset("assets/textures/tile.png");
        tileTexture->_filter = Harpia::Nearest;
        auto bustaTexture = LoadTextureAsset("assets/textures/busta.png");
        std::map<std::string, MeshAsset *> meshCollection;
        LoadFbxMeshAssets("assets/models/shapes.fbx", meshCollection);
        auto cubeMesh = meshCollection["Cube"];
        auto cylinderMesh = meshCollection["Cylinder"];
        auto sphereMesh = meshCollection["Sphere"];
        auto capsuleMesh = meshCollection["Capsule"];
        auto coneMesh = meshCollection["Cone"];
        auto axesMesh = meshCollection["Axes"];
        auto oldBox = LoadBoxMeshAsset(Vector<3>::zero, {1, 2, 3}, true);

        for (auto k: meshCollection) {
            DebugLog("Loaded mesh: %s", k.first.c_str());
        }

        auto floor = CreateObject("Floor");
        auto floorRend = floor->AddComponent<RendererComponent>();
        auto floorMat = LoadMaterialAsset(defaultShader);
        floorMat->SetColor(Color(0.5, 0.9, 0.3));
        floorMat->SetTexture(tileTexture);
        floorRend->SetMaterial(floorMat);
        auto floorMesh = LoadBoxMeshAsset({0, -2, -5}, {20, 1, 20}, true);
        floorRend->SetMesh(floorMesh);

        CreateRotatingShape({-10, 0, -5},
                            {1, 0, 0},
                            {1, 1, 1},
                            Color::orange,
                            defaultShader, tileTexture, oldBox);

        CreateRotatingShape({-7.5, 0, -10},
                            {1, 5, 0},
                            {1, 2, 1},
                            Color::green,
                            defaultShader, tileTexture, coneMesh);

        CreateRotatingShape({-5, 0, -5},
                            {3, 1, 0},
                            {1, 1, 1},
                            Color::azure,
                            defaultShader, tileTexture, cylinderMesh);

        CreateRotatingShape({5, 0, -5},
                            Vector3(2, 1, 2),
                            {1, 1, 1},
                            Color::white,
                            defaultShader, bustaTexture, axesMesh);

        CreateRotatingShape({7.5, 0, -10},
                            {1, 0, 5},
                            {1, 1, 1},
                            Color::rose,
                            defaultShader, tileTexture, capsuleMesh);

        CreateRotatingShape({10, 0, -5},
                            Vector3(0, 0, 3),
                            {2, 1, 1},
                            Color::purple,
                            defaultShader, tileTexture, sphereMesh);

        auto movableObject = CreateObject("Player");
        movableObject->AddComponent<CharacterController>();
        auto movableRend = movableObject->AddComponent<RendererComponent>();
        auto movableMat = LoadMaterialAsset(defaultShader);
        movableMat->SetTexture(bustaTexture);
        movableRend->SetMesh(capsuleMesh);
        movableRend->SetMaterial(movableMat);

        auto textObject = CreateObject("Text");
        textObject->transform.SetPosition({-5, 3, 0});
        auto textRenderer = textObject->AddComponent<TextRendererComponent>();
        auto fontAtlas = LoadTextureAsset("assets/fonts/pixel.png");
        fontAtlas->_filter = TextureFilter::Nearest;
        auto fontShader = LoadShaderAsset("assets/shaders/text.vert", "assets/shaders/text.frag");
        auto fontMaterial = LoadMaterialAsset(fontShader);
        fontMaterial->SetTexture(fontAtlas);
        fontMaterial->SetColor(Color::white);
        fontMaterial->_transparent = true;
        textRenderer->SetFontMaterial(fontMaterial, 7, 9);
        textRenderer->SetText("Hello World!");

        auto screenSize = application->screenSize;
        CreateCameraObject(application, RectInt{0, 0, screenSize.x / 2, screenSize.y}, movableObject);
        CreateCameraObject(application, RectInt{screenSize.x / 2, 0, screenSize.x / 2, screenSize.y}, nullptr);
    }

    void AllTheThingsScene::CreateCameraObject(const Application *application, const RectInt &viewport, Object *parent) {
        auto cameraObject = CreateObject("Camera");
        cameraObject->transform.SetParent(parent ? &parent->transform : nullptr);
        //cameraObject->transform.SetPosition({0, 5, 15.0f});
        //cameraObject->transform.Rotate(-15 * Math::Deg2Rad, {1, 0, 0});

        auto camera = cameraObject->AddComponent<CameraComponent>();
        //camera->SetPerspective(60.0f, (float) viewport.w / (float) viewport.h, 0.01f, 40.0f);
        camera->SetOrthographic(30, (float) viewport.w / (float) viewport.h, 40, -40);
        camera->SetViewport(viewport);
        camera->SetClearColor(Color(0.3f, 0.3f, 0.3f, 0.0f));
    }

    void AllTheThingsScene::CreateAudioObjects() {
        auto audioObject = CreateObject("Audio");

        auto audioComponent = audioObject->AddComponent<AudioComponent>();
        audioComponent->SetAudio(LoadAudioAsset("assets/audios/jump.wav"));

        auto music = audioObject->AddComponent<MusicComponent>();
        music->SetMusic(LoadMusicAsset("assets/musics/idle.ogg"));

        audioObject->AddComponent<TestAudio>();
    }
}// namespace SampleGame