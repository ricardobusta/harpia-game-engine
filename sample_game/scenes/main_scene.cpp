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
#include "rotate_around.h"
#include "test_audio.h"

using namespace Harpia;

namespace SampleGame {

    Harpia::Object *MainScene::CreateCube(const Vector3 &position, const Vector3 &rotatingSpeed, const Color &color,
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

        auto shader = LoadShaderAsset("assets/shader/test.vert", "assets/shader/test.frag");
        auto texture = LoadTextureAsset("assets/texture/busta.png");
        auto boxMesh = LoadBoxMeshAsset(Vector<3>::zero, Vector3(0.5f, 0.5f, 0.5f));

        CreateCube(
                Vector3(-1.7f, 0.0f, 0),
                Vector3(1.0f, 5.0f, 0),
                Color::orange,
                shader, texture, boxMesh);

        CreateCube(Vector3(1.7f, 0.0f, 0),
                   Vector3(5.0f, 1.0f, 0),
                   Color::azure,
                   shader, texture, boxMesh);

        CreateCube(Vector3(0.0f, -1.7f, 0),
                   Vector3(2, 2, 2),
                   Color::rose,
                   shader, texture, boxMesh);

        CreateCube(Vector3(0.0f, 1.7f, 0),
                   Vector3(0, 0, 5),
                   Color::purple,
                   shader, texture, boxMesh);

        auto cube = CreateCube(Vector3(0.0f, 0.0f, 0),
                   Vector3(0.0f, 0.0f, 0),
                   Color::aqua,
                   shader, texture, boxMesh);

        cube->transform.SetTrMatrix(cube->transform.GetTrMatrix() * Matrix::Rotation(45 * Math::Deg2Rad, {1, 1, 0}));
    }
}// namespace SampleGame