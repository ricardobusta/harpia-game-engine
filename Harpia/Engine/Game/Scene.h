//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_H
#define HARPIAGAMEENGINE_SCENE_H

#include "Internal/Scene_Internal.h"
#include "InternalDefines.h"
#include <string>
#include "HarpiaMath.h"

namespace Harpia {
    class Scene : private Internal::Scene_Internal {
    private:
    public:
        virtual void Load(Application *application) = 0;
        AudioAsset *LoadAudioAsset(const std::string &path);
        MusicAsset *LoadMusicAsset(const std::string &path);
        MaterialAsset *LoadMaterialAsset(ShaderAsset *shader);
        ShaderAsset *LoadShaderAsset();
        MeshAsset *LoadBoxMeshAsset(const Vector3 &pos, const Vector3 &size);
    protected:
        Object *CreateObject();
    private:
        void LoadScene(Application *application) override;
        MeshAsset *LoadMeshAsset(MeshAsset *asset);
    };

} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_H
