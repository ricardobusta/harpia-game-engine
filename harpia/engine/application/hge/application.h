//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include "hge/harpia_math.h"
#include "hge/in/application_internal.h"
#include <functional>
#include <list>

namespace Harpia {
    class Application : private Internal::Application_Internal {
    private:
        bool _createdWithSuccess = false;
        std::list<Internal::IApplicationSystem *> _systems;

    public:
        explicit Application(const std::function<void(Configuration &)> &configure);
        ~Application();
        int Execute();
        [[nodiscard]] int GetInitFlags() const;
        [[nodiscard]] int GetWindowFlags() const;
        [[nodiscard]] const Vector2& GetScreenSize() const;
        [[nodiscard]] float GetScreenAspect() const;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_APPLICATION_H
