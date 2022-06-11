//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "Scene.h"

#include <list>
#include "Object.h"
#include "Application_Internal.h"
#include "AudioSystem.h"
#include "RenderingSystem.h"

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

    MaterialAsset *Scene::LoadMaterialAsset(const Color &color) {
        auto asset = _applicationInternal->_renderSystem->LoadMaterial(color);
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadMeshAsset(int shape) {
        auto asset = _applicationInternal->_renderSystem->LoadMesh(shape);
        _assets.push_back(asset);
        return asset;
    }
} // Harpia