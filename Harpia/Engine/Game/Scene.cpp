//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "Scene.h"

#include <list>
#include "Object.h"
#include "Application_Internal.h"
#include "AudioSystem.h"

namespace Harpia {
    Object *Scene::CreateObject() {
        auto object = new Object(_applicationInternal);
        _objects.push_back(object);
        return object;
    }

    void Scene::LoadScene(Application *application) {
        Load(application);
    }

    AudioAsset *Scene::LoadAudio(const std::string &path) {
        auto asset = _applicationInternal->_audioSystem->LoadAudio(path);
        _assets.push_back(asset);
        return asset;
    }

    MusicAsset *Scene::LoadMusic(const std::string &path) {
        auto asset = _applicationInternal->_audioSystem->LoadMusic(path);
        _assets.push_back(asset);
        return asset;
    }
} // Harpia