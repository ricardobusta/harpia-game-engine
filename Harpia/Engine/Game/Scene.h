//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_H
#define HARPIAGAMEENGINE_SCENE_H

#include "Internal/Scene_Internal.h"
#include "InternalDefines.h"

namespace Harpia {
class Scene : private Internal::Scene_Internal {
    private:
    public:
        virtual void Load(Application *application) = 0;
    protected:
        Object *CreateObject();
    private:
        void LoadScene(Application *application) override;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_H
