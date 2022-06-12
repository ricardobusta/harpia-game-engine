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

    MeshAsset *Scene::LoadMeshAsset(MeshAsset *asset) {
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size) {
        auto sx = size.x / 2.0f;
        auto sy = size.y / 2.0f;
        auto sz = size.z / 2.0f;
        auto cx = pos.x;
        auto cy = pos.y;
        auto cz = pos.z;

        std::vector<GLfloat> v = {
                -sx + cx, -sy + cy, sz + cz,
                sx + cx, -sy + cy, sz + cz,
                sx + cx, sy + cy, sz + cz,
                -sx + cx, sy + cy, sz + cz,
        };
        std::vector<GLint> i = {0, 1, 2, 0, 2, 3};
        return LoadMeshAsset(_applicationInternal->_renderSystem->LoadMesh(v, i));
    }
} // Harpia