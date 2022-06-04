//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_CORESYSTEM_H
#define HARPIAGAMEENGINE_CORESYSTEM_H

namespace Harpia {

    class CoreSystem {
    public:
        virtual int GetInitFlags() = 0;

        virtual int GetWindowFlags() = 0;

        virtual void Quit() = 0;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_CORESYSTEM_H
