//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "scene.h"

#include "hge/audio_system.h"
#include "hge/harpia_string.h"
#include "hge/in/application_internal.h"
#include "hge/in/mesh_generator.h"
#include "hge/object.h"
#include "hge/rendering_system.h"
#include "hge/shader_asset.h"
#include "hge/texture_asset.h"
#include <list>

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
        auto asset = _applicationInternal->_renderSystem->CreateMaterial();
        asset->SetShader(shader);
        _assets.push_back(asset);
        return asset;
    }

    ShaderAsset *Scene::LoadShaderAsset(const std::string &vert, const std::string &frag) {
        DebugLog("Loading shader asset from %s and %s", vert.c_str(), frag.c_str());
        bool ok = false;

        auto vertSrc = Harpia::String::ReadFile(vert, &ok);
        if (!ok) {
            DebugLogError("Error when loading vertex shader file %s.", vert.c_str());
            return nullptr;
        }

        auto fragSrc = Harpia::String::ReadFile(frag, &ok);
        if (!ok) {
            DebugLogError("Error when loading fragment shader file %s.", frag.c_str());
            return nullptr;
        }

        auto asset = _applicationInternal->_renderSystem->LoadShader(vertSrc, fragSrc);
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadMeshAsset(MeshAsset *asset) {
        _assets.push_back(asset);
        return asset;
    }

    MeshAsset *Scene::LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size) {
        std::vector<float> v;
        std::vector<float> n;
        std::vector<float> t;
        std::vector<unsigned int> i;

        Internal::MeshGenerator::BoxMesh(v, n, t, i, pos, size);

        return LoadMeshAsset(_applicationInternal->_renderSystem->LoadMesh(v, n, t, i));
    }
    TextureAsset *Scene::LoadTextureAsset(const std::string &path) {
        auto asset = _applicationInternal->_renderSystem->LoadTexture(path);
        _assets.push_back(asset);
        return asset;
    }
}// namespace Harpia