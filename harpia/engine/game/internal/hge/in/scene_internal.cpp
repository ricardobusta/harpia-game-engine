//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "scene_internal.h"
#include "hge/asset.h"

namespace Harpia::Internal {
    void Scene_Internal::LoadInternal(Application *application) {
        _applicationInternal = (Internal::Application_Internal *) application;
        LoadScene(application);
        _loaded = true;
    }
}// namespace Harpia::Internal