//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/07/2022.
//

#include "spaceship_scene.h"
#include "hge/renderer_component.h"
#include "hge/color.h"
#include "hge/material_asset.h"
#include "hge/camera_component.h"
#include "hge/rect.h"
#include "hge/application.h"
#include "hge/texture_asset.h"
#include "spaceship_scene/player_spaceship_controller.h"

namespace SampleGame {
    void SpaceshipScene::Load(Application *application) {
        auto defaultShader = LoadShaderAsset("assets/shaders/default.vert", "assets/shaders/default.frag");
        auto tileTexture = LoadTextureAsset("assets/textures/blank.png");
        tileTexture->_filter = Harpia::Nearest;

        auto floor = CreateObject("Floor");
        auto floorRend = floor->AddComponent<RendererComponent>();
        auto floorMat = LoadMaterialAsset(defaultShader);
        floorMat->SetColor(Color::blue);
        floorMat->SetTexture(tileTexture);
        floorRend->SetMaterial(floorMat);
        auto floorMesh = LoadBoxMeshAsset({0, -2.25, 0}, {20, 1, 20}, true);
        floorRend->SetMesh(floorMesh);

        std::map<std::string, MeshAsset *> meshCollection;
        if(!LoadFbxMeshAssets("assets/spaceships/spaceships.fbx", meshCollection)){
            DebugLogError("Error!");
        }
        auto spaceshipMesh = meshCollection["Spaceship"];
        auto projectileMesh = meshCollection["Projectile"];
        for (auto k: meshCollection) {
            DebugLog("Loaded mesh: %s %d", k.first.c_str(), k.second);
        }

        auto player = CreateObject("Player");
        auto playerRenderer = player->AddComponent<RendererComponent>();
        auto playerMaterial = LoadMaterialAsset(defaultShader);
        auto playerTexture = LoadTextureAsset("assets/spaceships/ship01_tex.png");
        playerMaterial->SetTexture(playerTexture);
        playerMaterial->SetColor(Color::white);
        playerRenderer->SetMaterial(playerMaterial);
        playerRenderer->SetMesh(spaceshipMesh);
        player->transform.Rotate(180 * Math::Deg2Rad, {0,1,0});
        player->transform.SetPosition({0,0,5});
        auto playerController = player->AddComponent<PlayerSpaceshipController>();

        auto enemy01 = CreateObject("Enemy");
        auto enemy01Renderer = enemy01->AddComponent<RendererComponent>();
        auto enemyMaterial = LoadMaterialAsset(defaultShader);
        auto enemyTexture = LoadTextureAsset("assets/spaceships/ship02_tex.png");
        enemyMaterial->SetTexture(enemyTexture);
        enemyMaterial->SetColor(Color::white);
        enemy01Renderer->SetMaterial(enemyMaterial);
        enemy01Renderer->SetMesh(spaceshipMesh);
        enemy01->transform.SetPosition({0,0,-5});

        playerController->bullet1= CreateProjectile(playerMaterial, projectileMesh);
        playerController->bullet2= CreateProjectile(playerMaterial, projectileMesh);

        auto screenSize = application->screenSize;
        CreateCameraObject(false, RectInt{0,0, screenSize.x, screenSize.y}, nullptr);
        CreateCameraObject(true, RectInt{2*screenSize.x/3,2*screenSize.y/3, screenSize.x/3, screenSize.y/3}, nullptr);
    }

    void SpaceshipScene::CreateCameraObject(bool ortho, const RectInt &viewport, Object *parent) {
        auto cameraObject = CreateObject("Camera");
        cameraObject->transform.SetParent(parent ? &parent->transform : nullptr);

        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetViewport(viewport);

        if (ortho) {
            camera->SetOrthographic(10, (float) viewport.w / (float) viewport.h, 40, -40);
            cameraObject->transform.Rotate(45 * Math::Deg2Rad, {0, 1, 0});
            cameraObject->transform.Rotate(-45 * Math::Deg2Rad, {1, 0, 0});
            camera->SetClearColor(Color{0, 0, 0, 0});
            camera->SetClearType(CameraClearType::Depth);
        } else {
            camera->SetPerspective(60.0f, (float) viewport.w / (float) viewport.h, 0.01f, 40.0f);
            cameraObject->transform.SetPosition({0, 5, 15.0f});
            cameraObject->transform.Rotate(-15 * Math::Deg2Rad, {1, 0, 0});
            camera->SetClearColor(Color::darkGray);
        }
    }

    Object *SpaceshipScene::CreateProjectile(MaterialAsset *material, MeshAsset *mesh) {
        auto projectile = CreateObject("Projectile");
        auto renderer = projectile->AddComponent<RendererComponent>();
        renderer->SetMaterial(material);
        renderer->SetMesh(mesh);
        projectile->transform.SetPosition({1000,0,0});
        projectile->transform.SetScale({0,0,0});
        return projectile;
    }
}// namespace SampleGame