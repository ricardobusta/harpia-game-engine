//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include <functional>
#include "hge/in/Application_Internal.h"
#include "hge/HarpiaMath.h"

namespace Harpia {
    class Application : private Internal::Application_Internal {
    public:
        Vector2Int screenSize;
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
