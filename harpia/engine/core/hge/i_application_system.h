//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_IAPPLICATIONSYSTEM_H
#define HARPIAGAMEENGINE_IAPPLICATIONSYSTEM_H

namespace Harpia::Internal {

    class IApplicationSystem {
    public:
        virtual ~IApplicationSystem() = default;
        virtual int GetInitFlags() = 0;
        virtual int GetWindowFlags() = 0;
        virtual void Quit() = 0;
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_IAPPLICATIONSYSTEM_H
