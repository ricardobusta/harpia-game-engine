//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_H
#define HARPIAGAMEENGINE_SCENE_H

#include "hge/harpia_math.h"
#include "hge/in/scene_internal.h"
#include "hge/internal_defines.h"
#include "hge/object.h"
#include <map>
#include <string>

namespace Harpia {
    class Scene : private Internal::Scene_Internal {
    private:
    public:
        ~Scene() override;
        virtual void Load(Application *application) = 0;
        AudioAsset *LoadAudioAsset(const std::string &path);
        MusicAsset *LoadMusicAsset(const std::string &path);
        MaterialAsset *LoadMaterialAsset(ShaderAsset *shader);
        ShaderAsset *LoadShaderAsset(const std::string &vert, const std::string &frag);
        MeshAsset *LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size, bool tileUv);
        bool LoadFbxMeshAssets(const std::string &path, std::map<std::string, MeshAsset *> &meshes);
        TextureAsset *LoadTextureAsset(const std::string &path);
        void Release() override;

    protected:
        Object *CreateObject(const std::string &name);

    private:
        void LoadScene(Application *application) override;
        MeshAsset *LoadMeshAsset(MeshAsset *asset);
        void ReleaseImpl();
    };

}// namespace Harpia

#endif//HARPIAGAMEENGINE_SCENE_H
