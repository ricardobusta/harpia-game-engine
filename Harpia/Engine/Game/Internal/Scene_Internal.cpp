//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Scene_Internal.h"
#include "Asset.h"
#include "Debug.h"

namespace Harpia::Internal {
    void Scene_Internal::LoadInternal(Application *application) {
        _applicationInternal = (Internal::Application_Internal *) application;
        LoadScene(application);
    }

    void Scene_Internal::Release() {
        for (auto a: _assets) {
            a->Release();
        }
        _assets.clear();
        DebugLog("Scene released");
    }
} // Harpia