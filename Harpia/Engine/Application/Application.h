//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include <functional>
#include "Internal/Application_Internal.h"

namespace Harpia {
    class Application : private Application_Internal {
    private:
        bool _createdWithSuccess = false;
    public:
        explicit Application(const std::function<void(Configuration &)> &configure);

        ~Application();

        int Execute();

        int GetInitFlags();

        int GetWindowFlags();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
