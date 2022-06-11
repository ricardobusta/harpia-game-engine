//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESHASSET_H
#define HARPIAGAMEENGINE_MESHASSET_H

#include "Asset.h"

namespace Harpia {
    class MeshAsset : public Asset {
    public:
        void Release(Internal::Application_Internal *application) override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MESHASSET_H
