//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "main_scene.h"
#include "hge/debug.h"
#include "hge/audio_component.h"
#include "hge/music_component.h"
#include "hge/camera_component.h"
#include "test_audio.h"
#include "hge/application.h"
#include "hge/renderer_component.h"
#include "hge/color.h"
#include "hge/material_asset.h"
#include "rotate_around.h"

using namespace Harpia;

namespace SampleGame {
    void SampleGame::MainScene::Load(Harpia::Application *application) {
        DebugLog("Starting MainScene");

        auto audioObject = CreateObject();

        auto audioComponent = audioObject->AddComponent<AudioComponent>();
        audioComponent->SetAudio(LoadAudioAsset("assets/audio/jump.wav"));

        auto music = audioObject->AddComponent<MusicComponent>();
        music->SetMusic(LoadMusicAsset("assets/music/idle.ogg"));

        audioObject->AddComponent<TestAudio>();

        auto screenSize = application->screenSize;

        auto cameraObject = CreateObject();
        cameraObject->transform.SetTrMatrix(Matrix::Translation(Vector3{0, 0, -5.0f}));

        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetViewport(RectInt(0, 0, screenSize.x, screenSize.y));
        camera->SetClearColor(Color(0, 0, 0, 1));

        auto shader = LoadShaderAsset();
        auto texture = LoadTextureAsset("assets/texture/busta.png");

        auto cube1 = CreateObject();
        auto rotateScript1 = cube1->AddComponent<RotateAround>();
        rotateScript1->target = &cube1->transform;
        rotateScript1->speed = Vector3(1.0f, 5.0f, 0);
        cube1->transform.SetTrMatrix(Matrix::Translation(Vector3{-0.5f, 0.2f, 0}));
        auto rend1 = cube1->AddComponent<RendererComponent>();
        auto mat1 = LoadMaterialAsset(shader);
        mat1->SetTexture(texture);
        mat1->SetColor(Color::orange);
        rend1->SetMaterial(mat1);
        rend1->SetMesh(LoadBoxMeshAsset(Vector<3>::zero, Vector3(0.5f, 0.5f, 0.5f)));

        auto cube2 = CreateObject();
        auto rotateScript2 = cube1->AddComponent<RotateAround>();
        rotateScript2->target = &cube2->transform;
        rotateScript2->speed = Vector3(5.0f, 1.0f, 0);
        cube2->transform.SetTrMatrix(Matrix::Translation(Vector3{0.5f, -0.2f, 0}));
        auto rend2 = cube2->AddComponent<RendererComponent>();
        auto mat2 = LoadMaterialAsset(shader);
        mat2->SetColor(Color::azure);
        rend2->SetMaterial(mat2);
        rend2->SetMesh(LoadBoxMeshAsset(Vector<3>::zero, Vector3(0.5f, 0.5f, 0.5f)));
    }
}