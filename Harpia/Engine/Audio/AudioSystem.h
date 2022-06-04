//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSYSTEM_H
#define HARPIAGAMEENGINE_AUDIOSYSTEM_H

#include "CoreSystem.h"

namespace Harpia {
    class AudioConfiguration;

    class AudioSystem : public CoreSystem {
    public:
        int Initialize(AudioConfiguration &config);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSYSTEM_H
