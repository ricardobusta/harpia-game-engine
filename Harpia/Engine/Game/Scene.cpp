//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "Scene.h"

#include <list>
#include "Object.h"
#include "Application_Internal.h"
#include "AudioSystem.h"
#include "RenderingSystem.h"
#include "MeshGenerator.h"
#include "ShaderAsset.h"

namespace Harpia {
    Object *Scene::CreateObject() {
        auto object = new Object(_applicationInternal);
        _objects.push_back(object);
        return object;
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
        auto asset = new MaterialAsset(_applicationInternal->_renderSystem);
        asset->SetShader(shader);
        _assets.push_back(asset);
        return asset;
    }

    ShaderAsset *Scene::LoadShaderAsset(const Color &color) {
        auto asset = _applicationInternal->_renderSystem->LoadShader(color);
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadMeshAsset(MeshAsset *asset) {
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size) {
        std::vector<float> v;
        std::vector<int> i;

        Internal::MeshGenerator::BoxMesh(v, i, pos, size);

        return LoadMeshAsset(_applicationInternal->_renderSystem->LoadMesh(v, i));
    }
} // Harpia