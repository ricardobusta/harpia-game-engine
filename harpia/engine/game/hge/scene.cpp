//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "scene.h"

#include "hge/audio_system.h"
#include "hge/harpia_string.h"
#include "hge/in/application_internal.h"
#include "hge/mesh_generator.h"
#include "hge/object.h"
#include "hge/rendering_system.h"
#include "hge/shader_asset.h"
#include "hge/texture_asset.h"
#include <list>
#include "hge/rect.h"
#include "hge/camera_component.h"

namespace Harpia {
    Object *Scene::CreateObject(const std::string &name) {
        auto object = std::make_unique<Object>(name, _applicationInternal);
        object->InternalSetScene(this);
        _objects.push_back(std::move(object));
        return _objects.back().get();
    }

    void Scene::LoadScene(Application *application) {
        Load(application);
    }

    AudioAsset *Scene::LoadAudioAsset(const std::string &path) {
        auto asset = _applicationInternal->_audioSystem->LoadAudio(path);
        _assets.push_back(asset);
        return asset;
    }

    MusicAsset *Scene::LoadMusicAsset(const std::string &path) {
        auto asset = _applicationInternal->_audioSystem->LoadMusic(path);
        _assets.push_back(asset);
        return asset;
    }

    MaterialAsset *Scene::LoadMaterialAsset(ShaderAsset *shader) {
        auto asset = _applicationInternal->_renderSystem->CreateMaterial();
        asset->SetShader(shader);
        _assets.push_back(asset);
        return asset;
    }

    ShaderAsset *Scene::LoadShaderAsset(const std::string &vert, const std::string &frag) {
        HDebugLog("Loading shader asset from %s and %s", vert.c_str(), frag.c_str());

        auto asset = _applicationInternal->_renderSystem->LoadShader(vert, frag);
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadMeshAsset(MeshAsset *asset) {
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size, bool tileUv) {
        std::vector<float> v;
        std::vector<float> n;
        std::vector<float> t;
        std::vector<unsigned int> i;

        Internal::MeshGenerator::BoxMesh(v, n, t, i, pos, size, tileUv);

        return LoadMeshAsset(_applicationInternal->_renderSystem->LoadMesh(v, n, t, i));
    }

    bool Scene::LoadFbxMeshAssets(const std::string &path, std::map<std::string, MeshAsset *, std::less<>> &meshes) const{
        return _applicationInternal->_renderSystem->LoadFbxMeshes(path, meshes);
    }

    TextureAsset *Scene::LoadTextureAsset(const std::string &path) {
        auto asset = _applicationInternal->_renderSystem->LoadTexture(path);
        _assets.push_back(asset);
        return asset;
    }

    void Scene::Release() {
        ReleaseImpl();
    }

    void Scene::ReleaseImpl() {
        if (!_loaded) return;

        for (auto a: _assets) {
            a->Release();
        }
        _assets.clear();

        _objects.clear();

        _loaded = false;
        HDebugLog("Scene released %s", GetName().c_str());
    }

    Scene::~Scene() {
        ReleaseImpl();
    }

    CameraComponent *
    Scene::CreateSimplePerspectiveCamera(float fovy, float near, float far, const Vector3 &pos, float xAngle,
                                         const RectF &viewport, Object *parent) {
        auto cameraObject = CreateObject("Camera");
        cameraObject->transform.SetParent(parent ? &parent->transform : nullptr);

        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetViewport(viewport);

        camera->SetPerspective(fovy, near, far);
        cameraObject->transform.SetPosition(pos);
        cameraObject->transform.Rotate(xAngle * Math::Deg2Rad, {1, 0, 0});

        return camera;
    }

    CameraComponent *Scene::CreateSimpleOrthoCamera(float sizeV, const RectF &viewport) {
        auto cameraObject = CreateObject("Camera");
        auto camera = cameraObject->AddComponent<CameraComponent>();
        camera->SetOrthographic(sizeV, 1, -1);
        camera->SetViewport(viewport);

        return camera;
    }
}// namespace Harpia