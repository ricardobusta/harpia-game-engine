//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MainScene.h"
#include "Debug.h"
#include "AudioComponent.h"
#include "MusicComponent.h"
#include "CameraComponent.h"
#include "TestAudio.h"
#include "Application.h"
#include "RendererComponent.h"
#include "Color.h"

namespace SampleGame {
    void SampleGame::MainScene::Load(Harpia::Application *application) {
        DebugLog("Starting MainScene");

        auto audioObject = CreateObject();

        auto audioComponent = audioObject->AddComponent<Harpia::AudioComponent>();
        audioComponent->SetAudio(LoadAudioAsset("Assets/Audio/jump.wav"));

        auto music = audioObject->AddComponent<Harpia::MusicComponent>();
        music->SetMusic(LoadMusicAsset("Assets/Music/idle.ogg"));

        audioObject->AddComponent<TestAudio>();

        auto screenSize = application->screenSize;

        auto cameraObject = CreateObject();
        auto camera = cameraObject->AddComponent<Harpia::CameraComponent>();
        camera->SetViewport(Harpia::RectInt(0, 0, screenSize.x / 2, screenSize.y));
        camera->SetClearColor(Harpia::Color(0, 0, 0, 1));
        auto camera2 = cameraObject->AddComponent<Harpia::CameraComponent>();
        camera2->SetViewport(Harpia::RectInt(screenSize.x / 2, 0, screenSize.x / 2, screenSize.y));
        camera2->SetClearColor(Harpia::Color(0, 0, 0.5f, 1));

        auto cube1 = CreateObject();
        auto rend1 = cube1->AddComponent<Harpia::RendererComponent>();
        rend1->SetMaterial(LoadMaterialAsset(Harpia::Color(0.5f, 0, 0, 1)));
        rend1->SetMesh(LoadBoxMeshAsset(Harpia::Vector3(-0.5f,0,0), Harpia::Vector3(0.5f,0.5f,0.5f)));
        auto cube2 = CreateObject();
        auto rend2 = cube2->AddComponent<Harpia::RendererComponent>();
        rend2->SetMaterial(LoadMaterialAsset(Harpia::Color(0.0f, 0.5f, 0, 1)));
        rend2->SetMesh(LoadBoxMeshAsset(Harpia::Vector3(0.5f,0.3f,0), Harpia::Vector3(0.5f,0.5f,0.5f)));
    }
}