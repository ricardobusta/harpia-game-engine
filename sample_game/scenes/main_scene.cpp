//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "main_scene.h"
#include "hge/application.h"
#include "hge/audio_component.h"
#include "hge/camera_component.h"
#include "hge/color.h"
#include "hge/debug.h"
#include "hge/material_asset.h"
#include "hge/music_component.h"
#include "hge/renderer_component.h"
#include "hge/text_renderer_component.h"
#include "hge/texture_asset.h"
#include "rotate_around.h"
#include "test_audio.h"

using namespace Harpia;

namespace SampleGame {

    Harpia::Object *MainScene::CreateRotatingShape(const Vector3 &position, const Vector3 &rotatingSpeed, const Color &color,
                                                   ShaderAsset *shader, TextureAsset *texture, MeshAsset *mesh) {
        auto cube = CreateObject();
        auto rotateScript = cube->AddComponent<RotateAround>();
        rotateScript->target = &cube->transform;
        rotateScript->speed = rotatingSpeed;
        cube->transform.SetTrMatrix(Matrix::Translation(position));
        auto rend = cube->AddComponent<RendererComponent>();
        auto mat = LoadMaterialAsset(shader);
        mat->SetTexture(texture);
        mat->SetColor(color);
        rend->SetMaterial(mat);
        rend->SetMesh(mesh);
        return cube;
    }

    void MainScene::Load(Harpia::Application *application) {
        DebugLog("Starting MainScene");

        auto audioObject = CreateObject();

        auto audioComponent = audioObject->AddComponent<AudioComponent>();
        audioComponent->SetAudio(LoadAudioAsset("assets/audios/jump.wav"));

        auto music = audioObject->AddComponent<MusicComponent>();
        music->SetMusic(LoadMusicAsset("assets/musics/idle.ogg"));

        audioObject->AddComponent<TestAudio>();

        auto screenSize = application->screenSize;

        auto cameraObject = CreateObject();
        cameraObject->transform.SetTrMatrix(Matrix::Translation(Vector3{0, 0, -10.0f}));

        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetPerspective(60.0f, 640.0f / 480.0f, 0.01f, 20.0f);
        //camera->SetOrthographic(5, 640.0f / 480.0f, 0.01, 10);
        camera->SetViewport(RectInt(0, 0, screenSize.x, screenSize.y));
        camera->SetClearColor(Color(0.3f, 0.3f, 0.3f, 0.0f));

        auto shader = LoadShaderAsset("assets/shaders/default.vert", "assets/shaders/default.frag");
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
        auto oldBox = LoadBoxMeshAsset(Vector<3>::zero, {2, 2, 2});

        for (auto k: meshCollection) {
            DebugLog("Loaded mesh: %s", k.first.c_str());
        }

        CreateRotatingShape(
                Vector3(-4.0f, 0.0f, 0),
                Vector3(1.0f, 3.0f, 0),
                Color::orange,
                shader, tileTexture, cubeMesh);

        CreateRotatingShape(Vector3(4.0f, 0.0f, 0),
                            Vector3(3.0f, 1.0f, 0),
                            Color::azure,
                            shader, tileTexture, cylinderMesh);

        CreateRotatingShape(Vector3(0.0f, -4.0f, 0),
                            Vector3(2, 1, 2),
                            Color::white,
                            shader, bustaTexture, axesMesh);

        CreateRotatingShape(Vector3(0.0f, 4.0f, 0),
                            Vector3(0, 0, 3),
                            Color::purple,
                            shader, tileTexture, sphereMesh);

        auto textObject = CreateObject();
        //textObject->transform.SetTrMatrix(Matrix::Translation({0,1,0}));
        auto rotateScript = textObject->AddComponent<RotateAround>();
        rotateScript->target = &textObject->transform;
        rotateScript->speed = {0, 1, 0};
        auto textRenderer = textObject->AddComponent<TextRendererComponent>();
        auto fontAtlas = LoadTextureAsset("assets/fonts/pixel.png");
        fontAtlas->_filter = TextureFilter::Nearest;
        auto fontShader = LoadShaderAsset("assets/shaders/text.vert", "assets/shaders/text.frag");
        auto fontMaterial = LoadMaterialAsset(fontShader);
        fontMaterial->SetTexture(fontAtlas);
        fontMaterial->SetColor(Color::white);
        fontMaterial->_transparent = true;
        textRenderer->SetFontMaterial(fontMaterial,7,9);
        textRenderer->SetText("Hello World");
        //auto rend = textObject->AddComponent<RendererComponent>();
        //rend->SetMaterial(fontMaterial);
        //auto mesh = LoadBoxMeshAsset(Vector<3>::zero, {5,5,5});
        //rend->SetMesh(mesh);
    }
}// namespace SampleGame