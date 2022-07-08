//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESH_ASSET_H
#define HARPIAGAMEENGINE_MESH_ASSET_H

#include "hge/asset.h"
#include "hge/harpia_math.h"

namespace Harpia {
    class MeshAsset : public Asset {
    public:
        virtual void UpdateMesh()=0;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MESH_ASSET_H
