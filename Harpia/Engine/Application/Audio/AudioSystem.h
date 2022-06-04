//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_AUDIOSYSTEM_H
#define HARPIAGAMEENGINE_AUDIOSYSTEM_H

namespace Harpia {
    class AudioConfiguration;

    class AudioSystem {
    public:
        int Initialize(AudioConfiguration &config);

        int GetInitFlags();
    };

} // Harpia

#endif //HARPIAGAMEENGINE_AUDIOSYSTEM_H
